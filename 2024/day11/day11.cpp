

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

void blink(Stones &stone) {
   for (auto it = stones.begin(); it != stones.end(); ++it) {
      if (*it == 0) {
        *it = 1;
        return;
      }
      auto size = static_cast<long>(std::log10(*it) + 1);
      if ((size % 2) == 0) {
          auto div = std::div(*it, );

      }
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
}

