

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <format>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <ranges>
#include <regex>


struct Pos {
  long long x = 0, y = 0;
  friend auto format_as(const Pos &p) {
    return fmt::format("(X={}, Y={})", p.x, p.y);
  }
};

using Map = std::vector<std::string>;

using List = std::vector<Pos>;

std::optional<size_t> find_path(int x, int y, size_t score, Map& map, const Pos& end) {
   if (map[y][x] == '#' or map[y][x] == 'V') return {};
   if (y == end.y && x == end.x) return score;

   map[y][x] = 'V';
   auto res = std::optional<size_t>{};
   for (auto score : { find_path(x + 1, y, score + 1, map, end), 
                       find_path(x - 1, y, score + 1, map, end),
                       find_path(x, y + 1, score + 1, map, end),
                       find_path(x, y - 1, score + 1, map, end) }) {
       if (not res) res = score;
       if (res and score and *res > *score) res = score;
   }

   map[y][x] = '.';
   return res; 
}

int main() {

  auto list = List{};
  auto input = std::string{};
  std::regex r(R"((\d+),(\d+))");
  std::smatch sm;
  while (getline(std::cin, input)) {
      regex_search(input, sm, r);
      list.emplace_back(stol(sm[1].str()), stol(sm[2].str()));
  }
  fmt::print("List is:\n{}\n", list);

  auto map_size = 70;
  auto limit = 1024;
  if (list.size() == 25) {
      map_size = 7;
      limit = 12;
  }
  map_size += 2;

  auto map = Map(map_size);
  for (auto &l : map) {
     l.resize(map_size, '.');
     l[0] = l.back() = '#';
  }
  std::ranges::fill(map.front(), '#');
  std::ranges::fill(map.back(), '#');

  for (auto i = 0u; i < limit; i++) {
      auto&p = list[i];
      map[p.y + 1][p.x + 1] = '#';
  }
  //map[map_size - 2][map_size - 2] = 'O';
  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));

 auto size = find_path(1, 1, 0, map, Pos{map_size - 2, map_size -2 });
 fmt::print("Size {}\n", size);
}


