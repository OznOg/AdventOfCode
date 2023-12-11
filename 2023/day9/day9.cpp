#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <optional>


using History = std::vector<unsigned>;

using Data = std::vector<History>;

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       auto ss = std::stringstream{input};
       unsigned val;
       History h;
       while (ss >> val) {
           h.push_back(val); 
       }
       data.emplace_back(std::move(h));
    }

   std::cout << data.size() << '\n';

    auto all_zero = [] (const auto &v) {
      return std::find_if(v.begin(), v.end(), [] (auto &e) { return e != 0; }) == std::end(v);
    };

   auto job = std::map<unsigned, std::vector<History>>{};
   auto idx = unsigned{0};
   for (auto &h : data) {
      auto &j = job[idx]; 
      j.emplace_back(h); // copy original history
      while (not all_zero(j.back())) {
         auto &ref = j.back();
         History diff;
         for (int i = 1; i < ref.size(); i++) {
           diff.push_back(ref[i] - ref[i - 1]);
         }
         j.emplace_back(std::move(diff));
      }
      idx++;
   }
   std::cout << job.size() << '\n';


   // extrapolate
   auto sum = unsigned{0};
   for (auto &[idx, j] : job) {
      std::optional<unsigned> prev;
      for (auto it = j.rbegin(); it != j.rend(); it++) {
         if (prev) {
             prev = *prev + it->back();
         } else
             prev = it->back();
      }
      sum += *prev;
   }

   std::cout << "Sum is: " << sum << '\n';
   

}


