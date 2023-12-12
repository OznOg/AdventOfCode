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


using Line = std::string;
using Data = std::vector<Line>;

auto colum_has_galaxy(const Data&data, unsigned idx) {
    for (auto &l : data) {
      if (l[idx] == '#') return true;
    }
    return false;
}

auto line_has_galaxy(const Data&data, unsigned idx) {
    for (auto &c : data[idx]) {
      if (c == '#') return true;
    }
    return false;
}

Data expand(const Data& data) {
    Data expanded;
     
    for (auto idx = 0u; idx < data.size(); idx++) {
       if (not line_has_galaxy(data, idx)) {
           expanded.emplace_back(data[idx].size(), 'X');
       } else {
           expanded.emplace_back(data[idx]);
       }
    }

    for (auto idx = 0u; idx < expanded.front().size(); idx++) {
       if (not colum_has_galaxy(expanded, idx)) {
           for (auto &l : expanded) {
               l[idx] = 'X';
           }
       }
    }
    return expanded;
}

auto soft_line_diff(const Data& data, unsigned a, unsigned b) {
    unsigned dist = 0;
    if (a < b) {
      std::swap(a, b);
    }
    for (auto idx = b; idx < a; idx++) {
        if (data[idx][0] != 'X')
            dist++;
        else
            dist += 1'000'000u;
    }
    return dist;
}
auto soft_col_diff(const Data& data, unsigned a, unsigned b) {
    unsigned dist = 0;
    if (a < b) {
      std::swap(a, b);
    }
    for (auto idx = b; idx < a; idx++) {
        if (data[0][idx] != 'X')
            dist++;
        else
            dist += 1'000'000u;
    }
    return dist;
}
unsigned distance(const Data& data, const std::pair<unsigned, unsigned> &p1, const std::pair<unsigned, unsigned> &p2) {
      auto &[x1, y1] = p1;
      auto &[x2, y2] = p2;

      return soft_col_diff(data, x1, x2) + soft_line_diff(data, y1, y2);
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       data.emplace_back(input);
    }

   std::cout << data.size() << '\n';

   auto expanded = expand(data);

   for (const auto &l : expanded) {
       std::cout << l << '\n';
   }


   std::vector<std::pair<unsigned, unsigned>> galaxies;

   for (const auto &l : expanded) {
       for (const auto &c : l) {
           if (c == '#')
               galaxies.emplace_back(std::make_pair(&c - &l[0], &l - &expanded[0]));
       }
   }
   std::cout << "Number of galaxies: " << galaxies.size() << '\n';

   std::vector<std::tuple<unsigned, unsigned, unsigned>> combinaisons;

   for (auto idx = 0u; idx < galaxies.size(); idx++) {
       for (auto idx2 = idx + 1; idx2 < galaxies.size(); idx2++) {
           combinaisons.emplace_back(std::make_tuple(idx, idx2, 0 /* distance */));
       }
   }
   std::cout << "Number of cominaisons: " << combinaisons.size() << '\n';

   auto sum = 0ul;
   for (auto &[id1, id2, dist] : combinaisons) {
      dist = distance(expanded, galaxies[id1], galaxies[id2]);
      std::cout << "(" << id1 << "," << id2 << ") " << dist << '\n';
      sum += dist;
   }
   
   std::cout << "Sum is: " << sum << '\n';
}


