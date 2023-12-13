#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <set>
#include <optional>

using Springs = std::pair<std::string, std::vector<unsigned>>;
using Data = std::vector<Springs>;

unsigned matches(const std::string &l, std::vector<unsigned> &group) {
    auto g = std::vector<unsigned>{};
    g.push_back(0);
    unsigned idx = 0;
    while (idx < l.size()) {
        if (l[idx] == '.') {
            if (g.back() != 0)
               if (g.back() != group[g.size() - 1])
                   return 0;
               else
                   g.push_back(0);
        } else {
            g.back()++;
        }
        idx++;
    }
    if (g.back() == 0)
      g.resize(g.size() - 1);
    return g == group;
}

unsigned do_the_job(const std::string &l, std::vector<unsigned> &group, std::vector<unsigned> ref = {{0}}, size_t pos = 0) {
   
    if (pos == l.size()) {
        if (ref.back() == 0)
            ref.resize(ref.size() - 1);
        return ref == group;
    }
    
    if (l[pos] == '#') {
        ref.back()++;
        if (ref.back() > group[ref.size() - 1]) return 0;
        return do_the_job(l, group, ref, pos + 1);
    }
    if (l[pos] == '.') {
        if (ref.back() != 0) {
            if (ref.back() != group[ref.size() - 1])
                return 0;
            else
                ref.push_back(0);
        }
        return do_the_job(l, group, ref, pos + 1);
    }
    if (l[pos] == '?') {
        auto l2 = l;
        l2[pos] = '#';
        auto c = do_the_job(l2, group, ref, pos);
        l2[pos] = '.';
        return c + do_the_job(l2, group, ref, pos);
    }
    throw "WTF";
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       auto groups_str = std::string{};
       Springs spring;
       auto ss = std::stringstream{input};
       ss >> spring.first >> groups_str; 

       while (not groups_str.empty()) {
          auto pos = groups_str.find(',');
          spring.second.push_back(std::stoi(groups_str.substr(0, pos)));
          if (pos != std::string::npos) { 
            pos++;
            groups_str = groups_str.substr(pos);
          } else groups_str.clear();
       }
       

       data.emplace_back(std::move(spring));
    }

   unsigned long sum = 0;
   #if 0
   for (auto &[l, g] : data) {
       auto count = do_the_job(l, g);
       sum += count;
   }
   #endif

   std::cout << "Sum is: " << sum << '\n';

   auto unfolded_data = data;
   for (auto &[l, g] : unfolded_data) {
       l = l + '?' + l + '?' + l + '?' + l + '?' + l;
       auto g2 = g;
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g = g2;
   }

   for (auto &[l, g] : unfolded_data) {
       std::cout << "processing: " << l;
       auto count = do_the_job(l, g);
       std::cout << " " << count << '\n';
       sum += count;
   }

   std::cout << "Sum is: " << sum << '\n';

}


