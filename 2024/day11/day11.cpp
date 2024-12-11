

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

using History = std::map<unsigned long long, std::map<unsigned, unsigned long long>>;


unsigned long long blink(size_t count, unsigned long long val, History& history) {
      auto maybe = history[val][count];

      if (maybe != 0) return maybe;

      if (count == 0) return 1;

      if (val == 0) {
        auto nb = blink(count - 1, 1, history);
        history[val][count] = nb;
        return nb;
      }

      auto size = static_cast<long>(std::log10(val) + 1);
      if ((size % 2) == 0) {
        auto div = std::lldiv(val, my_exp10(size / 2));
        auto nb = blink(count - 1, div.quot, history) + blink(count - 1, div.rem, history);
        history[val][count] = nb;
        return nb;
      }

      auto nb = blink(count - 1, val * 2024, history);
      history[val][count] = nb;
      return nb;
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

  auto history = History{};
  unsigned long long sum = 0;

  for (auto s : data) {
    sum += blink(75, s, history);
  }
  fmt::print("After 75 blink: {}\n", sum);
}

