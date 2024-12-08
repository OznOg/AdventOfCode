


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cctype>
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


using Map = std::vector<std::string>;

struct Antenna {
  int x, y;
  friend auto format_as(const Antenna& a) {
      return fmt::format("({}, {})", a.x, a.y);
  }
};

using AllAntennas = std::map<unsigned char, std::vector<Antenna>>;

void interfere(std::vector<Antenna> va, Map &map) {
   if (va.size() <= 1) return;

   auto a = va.back();
   va.pop_back();
   for (auto &i : va) {
      auto dx = 2 * i.x - a.x;
      auto dy = 2 * i.y - a.y;
      auto Dx = -i.x + 2 * a.x;
      auto Dy = -i.y + 2 * a.y;
      auto dropd = dx != std::clamp<int>(dx, 0, map[0].size() -1) or
                   dy != std::clamp<int>(dy, 0, map.size() -1);
      auto dropD = Dx != std::clamp<int>(Dx, 0, map[0].size() -1) or
                   Dy != std::clamp<int>(Dy, 0, map.size() -1);
      if (not dropd)
          map[dy][dx] = '#';
      if (not dropD)
          map[Dy][Dx] = '#';
   }
   interfere(va, map);
}

int main() {

  auto map = Map{};
  auto all = AllAntennas{};

  auto input = std::string{};
  auto idx = 0;
  while (getline(std::cin, input)) {
      map.emplace_back(std::string(input.size(), '.'));
      for (auto i = 0; i < input.size(); i++) {
           if (isalnum(input[i])) {
              all[input[i]].emplace_back(i, idx);
           }
      }
      idx++;
  }

  fmt::print("{}\n", all);

  for (const auto &[f, a] : all) {
     interfere(a, map);
  }
  
  fmt::print("{}\n", fmt::join(map, "\n"));
  auto count = 0u;
  for (const auto &c : fmt::format("{}", fmt::join(map, ""))) {
      if (c == '#') count++;
  }
  fmt::print("Count is: {}\n", count);
}

