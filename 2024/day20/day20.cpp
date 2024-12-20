

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
std::optional<size_t> find_path(int x, int y, size_t score, Map& map, const Pos& end, std::optional<Pos> cheat = {}, std::vector<unsigned> *cheat_score ={}) {
    if (x == 0 or x == map[0].size() or y == 0 or y == map.size()) return {};
    auto res = std::optional<size_t>{};

    if (cheat and cheat->x == x and cheat->y == y) {
        for (auto i : {-1, 1}) {
           if (map[y][x + i] == '#') {
             map[y][x + i] = '.';
             auto val = find_path(x, y, score, map, end);
             if (val) cheat_score->emplace_back(*val);
             if (not res) res = val;
             if (res and val and *res > *val){
                res = val;
             }
             map[y][x + i] = '#';
           }
           if (map[y + i][x] == '#') {
             map[y + i][x] = '.';
             auto val = find_path(x, y, score, map, end);
             if (val) cheat_score->emplace_back(*val);
             if (not res) res = val;
             if (res and val and *res > *val) res = val;
             map[y + i][x] = '#';
           }
        }
        return res;
    }
    
   if (map[y][x] == '#' or map[y][x] == 'V') return {};
   if (y == end.y && x == end.x) return score;

   map[y][x] = 'V';
   for (auto val : { find_path(x + 1, y, score + 1, map, end, cheat, cheat_score), 
                       find_path(x - 1, y, score + 1, map, end, cheat, cheat_score),
                       find_path(x, y + 1, score + 1, map, end, cheat, cheat_score),
                       find_path(x, y - 1, score + 1, map, end, cheat, cheat_score) }) {
       if (not res) res = val;
       if (res and val and *res > *val) res = val;
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
  auto map = Map{};
  auto idx = 0;
  Pos start, end;
  while (getline(std::cin, input)) {
      map.emplace_back(input);
      auto pos = input.find('S');
      if (pos != std::string::npos) {
        start.x = pos;
        start.y = idx;
      }
      pos = input.find('E');
      if (pos != std::string::npos) {
        end.x = pos;
        end.y = idx;
      }
      idx++;
  }
  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));


  auto ref_size = find_path(start.x, start.y, 0, map, end);
  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));
  fmt::print("size is:\n{}\n", ref_size);
  //fmt::print("Scores are:\n{}\n", fmt::join(scores, "\n"));
  //
  auto track = std::vector<Pos>{};
  auto nb_char = 0;

  for (auto y= 0; y < map.size(); y++) {
    for (auto x= 0; x < map[0].size(); x++) {
         if (map[y][x] == '.') track.emplace_back(x, y);
    }
  }
  fmt::print("char is:\n{}\n", track.size());

  auto count = 0;
  for (auto t: track) {
    fmt::print("Testing : {}\n", t);
     
     std::vector<unsigned> cs;
     find_path(start.x, start.y, 0, map, end, t, &cs);
     for (auto &val : cs)
       if (val + 100 <= ref_size) count++;
  }
  fmt::print("Count is:\n{}\n", count);
}


