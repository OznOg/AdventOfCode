

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <format>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <ranges>
#include <regex>

using Stones = std::list<unsigned long long>;

unsigned long long my_exp10(unsigned pow) {
    unsigned long long res = 1;
    for (auto i = 0; i < pow; i++) {
       res *= 10;
    }
    return res;
}

void blink(Stones &stones) {
   for (auto it = stones.begin(); it != stones.end(); ++it) {
      if (*it == 0) {
        *it = 1;
        continue;
      }
      auto size = static_cast<long>(std::log10(*it) + 1);
      if ((size % 2) == 0) {
          auto div = std::lldiv(*it, my_exp10(size / 2));
          stones.insert(it, div.quot);
          *it = div.rem;
          continue;
      }

      *it *= 2024;
   }
}

int main() {

  auto data = Stones{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      auto ss = std::stringstream{input};
      unsigned val;
      while (ss >> val) {
         data.push_back(val);
      }
  }

  fmt::print("Data is: {}\n", data);

  for (auto i = 0; i < 25; i++) {
    blink(data);
  }
  fmt::print("After 25 blink: {}\n", data.size());
}

