


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

bool is_out(int x, int y, const Map& map) {
    return x != std::clamp<int>(x, 0, map[0].size() -1) or
        y != std::clamp<int>(y, 0, map.size() -1);
}
void interfere(std::vector<Antenna> va, Map &map, bool p2 = false) {
   auto a = va.back();
   if (p2)
       map[a.y][a.x] = '#';

   if (va.size() <= 1) return;

   va.pop_back();
   for (auto &i : va) {
      int dx = i.x;
      int dy = i.y;
      do {
          dx += i.x - a.x;
          dy += i.y - a.y;
          auto dropd = is_out(dx, dy, map);
          if (not dropd)
              map[dy][dx] = '#';
          else
            break;
      } while(p2);

      int Dx = a.x;
      int Dy = a.y;
      do {
          Dx += -i.x + a.x;
          Dy += -i.y + a.y;
          auto dropD = is_out(Dx, Dy, map);
          if (not dropD)
              map[Dy][Dx] = '#';
          else
            break;
      } while(p2);
   }
   interfere(va, map, p2);
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

  { //p1
      for (const auto &[f, a] : all) {
          interfere(a, map);
      }

      auto count = 0u;
      for (const auto &c : fmt::format("{}", fmt::join(map, ""))) {
          if (c == '#') count++;
      }
      fmt::print("{}\n", fmt::join(map, "\n"));
      fmt::print("Count is: {}\n", count);
  }
  { // p2
      for (const auto &[f, a] : all) {
          interfere(a, map, true);
      }

      auto count = 0u;
      for (const auto &c : fmt::format("{}", fmt::join(map, ""))) {
          if (c == '#') count++;
      }
      fmt::print("{}\n", fmt::join(map, "\n"));
      fmt::print("Count is: {}\n", count);
  }
}

