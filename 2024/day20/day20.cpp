

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
  bool operator==(const Pos&) const = default;
  friend auto format_as(const Pos &p) {
    return fmt::format("(X={}, Y={})", p.x, p.y);
  }
};

using Map = std::vector<std::string>;

using Path = std::map<int, std::map<int, unsigned>>;

std::optional<size_t> find_path(int x, int y, size_t score, Map& map, const Pos& end, Path &path) {
  if (x == 0 or x == map[0].size() or y == 0 or y == map.size()) return {};
  auto res = std::optional<size_t>{};
  if (map[y][x] == '#' or map[y][x] == 'V') return {};
  if (y == end.y && x == end.x) {
    path[y][x] = score;
    return score;
  }

  map[y][x] = 'V';
  for (auto val : { find_path(x + 1, y, score + 1, map, end, path), 
      find_path(x - 1, y, score + 1, map, end, path),
      find_path(x, y + 1, score + 1, map, end, path),
      find_path(x, y - 1, score + 1, map, end, path) }) {
    if (not res) res = val;
    if (res and val and *res > *val) res = val;
  }

  map[y][x] = '.';
  if (res) path[y][x] = score;
  return res; 
}

template<unsigned dist, unsigned cheat_duration>
std::vector<Pos> find_path_around(const int& x, const int& y, unsigned score, const Path& path) {
  auto res = std::vector<Pos>{};
  for (auto i = 0; i <= dist; i++) {
    for (auto j = 0; j + i <= dist ; j++) {
       if (j == 0 and i == 0) continue;
       auto x1 = x + i;
       auto x2 = x - i;
       auto y1 = y + j;
       auto y2 = y - j;

       if (path.contains(y1) and path.at(y1).contains(x1) and path.at(y1).at(x1) >= score + i + j + cheat_duration) {
           res.emplace_back(x1, y1);
       }
       if (path.contains(y2) and path.at(y2).contains(x1) and path.at(y2).at(x1) >= score + i + j + cheat_duration) {
           res.emplace_back(x1, y2);
       }
       if (path.contains(y1) and path.at(y1).contains(x2) and path.at(y1).at(x2) >= score + i + j + cheat_duration) {
           res.emplace_back(x2, y1);
       }
       if (path.contains(y2) and path.at(y2).contains(x2) and path.at(y2).at(x2) >= score + i + j + cheat_duration) {
           res.emplace_back(x2, y2);
       }
    }
  }
  return res;
}

int main() {

  auto input = std::string{};
  auto map = Map{};
  auto idx = 0;
  Pos start, end;
  while (getline(std::cin, input)) {
      auto pos = input.find('S');
      if (pos != std::string::npos) {
        start.x = pos;
        start.y = idx;
        input[pos] = '.';
      }
      pos = input.find('E');
      if (pos != std::string::npos) {
        end.x = pos;
        end.y = idx;
        input[pos] = '.';
      }
      map.emplace_back(input);
      idx++;
  }
  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));
  fmt::print("Start is: {}\n", start);
  fmt::print("End is: {}\n", end);

  auto path = Path{};
  auto ref_size = find_path(start.x, start.y, 0, map, end, path);
  fmt::print("size is:\n{}\n", ref_size);
//  fmt::print("Path is:\n{}\n", fmt::join(path, "\n"));

  { // p1
    auto count = 0;
    for (auto &[y, mX] : path) {
      for (auto &[x, s] : mX) {
        auto around = find_path_around<2, 100>(x, y, s, path);
        std::ranges::sort(around, [](const auto &a, const auto &b) { return a.y < b.y or (a.y == b.y and a.x < b.x); });
        around.erase(std::unique(around.begin(), around.end() ), around.end());

        //fmt::print("for {} {} {}\n", x, y, around.size());
        count += around.size();
      }
    }
    fmt::print("Count p1 is: {}\n", count);
  }
  { //p2
    auto count = 0;
    for (auto &[y, mX] : path) {
      for (auto &[x, s] : mX) {
        auto around = find_path_around<20, 100>(x, y, s, path);
        std::ranges::sort(around, [](const auto &a, const auto &b) { return a.y < b.y or (a.y == b.y and a.x < b.x); });
        around.erase(std::unique(around.begin(), around.end() ), around.end());

        //fmt::print("for {} {} {}\n", x, y, around.size());
        count += around.size();
      }
    }
    fmt::print("Count p2 is: {}\n", count);
  }
}


