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

unsigned count_matches(const std::string &l, std::vector<unsigned> &group) {
    auto g = std::vector<unsigned>{};
    g.push_back(0);
    unsigned idx = 0;
    while (idx < l.size()) {
        if (l[idx] == '.') {
            if (g.back() != 0)
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

unsigned do_the_job(std::string l, std::vector<unsigned> &group) {
  
    auto pos = l.find('?');

    if (pos == std::string::npos) {
       // check matches
       return count_matches(l, group);
    }

    l[pos] = '#';
    auto c = do_the_job(l, group);
    l[pos] = '.';

    return c + do_the_job(l, group);
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       auto groups_str = std::string{};
       Springs spring;
       auto ss = std::stringstream{input};
       ss >> spring.first >> groups_str; 

       spring.first = '.' + spring.first + '.'; // make sure some empty stuff is on side (eases search)

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
   for (auto &[l, g] : data) {
       auto count = do_the_job(l, g);
       sum += count;
   }

   std::cout << "Sum is: " << sum << '\n';

}


