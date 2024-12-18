

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

using Scores = std::map<unsigned, std::map<unsigned, std::optional<unsigned>>>;

// direct find_path, works on small maze but not on large one because it crawls
// the whole map (and as the map has very large areas without walls)
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

auto find_best_around(int x, int y, Scores& scores) {
   
   auto res = std::optional<size_t>{};
   for (auto &score : { scores[y][x + 1], scores[y][x - 1], scores[y + 1][x], scores[y - 1][x] }) {
       if (not res) res = score;
       if (res and score and *res > *score) res = score;
   }
   return res;
}

// This implementation works by updating values on a diagonal; As there may be
// some places behind walls that are unreachable on first pass, this needs to
// be called again and again until it returns false
bool dijkstra(const Map& map, Scores& scores) {
  scores[1][1] = 0;

  auto res = false;
  for (auto i = 1; i < map.size() * 2; i++) {
     for (auto x = 0; x <= i; x++) {
       auto y = i - x;
       if (y >= map.size() or x >= map.size()) continue;
       if (map[y][x] != '#' && not scores[y][x]) {
         auto best = find_best_around(x, y, scores);
         if (best) {
           scores[y][x] = *best + 1;
           res = true;
         }
       }
     }
  }
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

  auto map_size = 71;
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
  // add # all around the map to ease the path finding later (no need to check
  // for bounds, just stop when a # is found
  std::ranges::fill(map.front(), '#');
  std::ranges::fill(map.back(), '#');

  for (auto i = 0u; i < limit; i++) {
      auto&p = list[i];
      map[p.y + 1][p.x + 1] = '#';
  }
  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));

  { // p1
    Scores scores;
    while(not scores[map_size - 2][map_size - 2]) {
      dijkstra(map, scores);
    }
    fmt::print("Size {}\n", scores[map_size - 2][map_size - 2]);
  }
  { // p2

    // auto size = find_path(1, 1, 0, map, Pos{map_size - 2, map_size -2 });
    //  fmt::print("Scores are:\n{}\n", fmt::join(scores, "\n"));

    auto end = list.end();
    auto begin = list.begin();
    auto it = end;

    // dichotomy to find the elements that breaks the path
    do {
      auto test_map = map;
      for (auto it2 = list.begin() + 1024; it2 != it; it2++) {
        auto&p = *it2;
        test_map[p.y + 1][p.x + 1] = '#';
      }
      Scores scores;
      while(not scores[map_size - 2][map_size - 2]) {
        auto changed = dijkstra(test_map, scores);
        if (not changed) {
          break;
        }
      }

      auto good = scores[map_size - 2][map_size - 2].has_value();

      fmt::print("====> {} {} {}\n", good, std::distance(list.begin(), it), std::distance(begin, end) );
      begin = (good ? it : begin);
      end = good ? end :it;
      it = begin + std::distance(begin, end) / 2;
      good = false;

    } while(std::distance(begin, end) != 1);

    fmt::print("First bad is: {},{}\n", begin->x, begin->y);
  }
}


