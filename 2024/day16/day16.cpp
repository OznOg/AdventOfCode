

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
#include <map>
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

struct Reindeer {
  
  enum class Direction { N, E, S, O };

  bool operator==(const Reindeer&) const = default;

  Direction dir;

  Pos  pos;

  std::vector<Pos> path;

  unsigned score = 0;
};

std::string format_as(const Reindeer::Direction &dir) {
  switch(dir) {
    case Reindeer::Direction::N : return "N";
    case Reindeer::Direction::S : return "S";
    case Reindeer::Direction::E : return "E";
    case Reindeer::Direction::O : return "O";
  }
}

auto format_as(const Reindeer &r) {
  return fmt::format("Reindeer: {} {}", r.pos, r.dir);
}
using History = std::map<unsigned long long, std::map<unsigned, std::map<Reindeer::Direction, unsigned>>>;

std::vector<std::pair<unsigned, std::vector<Pos>>> sc;

std::vector<Reindeer> crawl_region(Reindeer &r, Map &map, History& history) {

    auto next = std::vector<Reindeer>{};

    if (map[r.pos.y][r.pos.x] == 'E') {
       //fmt::print("===============>{}\n", r.score);
       history[r.pos.y][r.pos.x][r.dir] = r.score;
       sc.push_back(std::make_pair(r.score, r.path));
       return {};
    }
    switch(r.dir) {
        case Reindeer::Direction::N:
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            } 
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score) {
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.pos.x--;
                rn.dir = Reindeer::Direction::O;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            break;

        case Reindeer::Direction::O:
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.pos.x--;
                rn.dir = Reindeer::Direction::O;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            break;

        case Reindeer::Direction::S:
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.dir = Reindeer::Direction::O;
                rn.pos.x--;
                rn.score += 1001;
                rn.dir = Reindeer::Direction::O;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            } 
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            break;

        case Reindeer::Direction::E:
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score){
                  rn.path.emplace_back(rn.pos);
                    next.emplace_back(rn);
                }
            }
            break;
    }
    history[r.pos.y][r.pos.x][r.dir] = r.score;
    return next;
}

int main() {

  auto reindeer = Reindeer{};
  auto map = Map{};
  auto input = std::string{};
  auto idx = 0;
  Pos end{};
  while (getline(std::cin, input)) {
      if (input.size() == 0) break;
      auto pos = input.find('S');
      if (pos != std::string::npos) {
        reindeer.pos.x = pos;
        reindeer.pos.y = idx;
        reindeer.dir = Reindeer::Direction::E;
        input[pos] = '.';
      }
       pos = input.find('E');
      if (pos != std::string::npos) {
        end.x = pos;
        end.y = idx;
      }
      map.push_back(input);
      idx++;
  }

  fmt::print("Reindeer:\n{}\n", reindeer);
  fmt::print("Map:\n{}\n", fmt::join(map, "\n"));
  History h;

  auto v = crawl_region(reindeer, map, h);
  while (!v.empty()) {
     auto v2 = std::vector<Reindeer>{}; 
    for (auto &r : v) {
        auto v3 = crawl_region(r, map, h);
        v2.insert(v2.end(), v3.begin(), v3.end());
    }
    v = v2;
  }

  
  auto best = static_cast<unsigned>(-1);

  for (auto &[s, p]: sc) {
      if (s < best) best = s;
  }
  for (auto &[s, p]: sc) {
      if (s == best) {
        fmt::print("Path :\n{}\n", p);
        for (auto&pos : p)
          map[pos.y][pos.x] = 'O';
      }
  }
  fmt::print("Sc:\n{}\n", best);
  fmt::print("Map:\n{}\n", fmt::join(map, "\n"));
  //fmt::print("History:\n{}\n", fmt::join(h, "\n"));

  auto count = 0;

  for (auto &l : map) {
    for (auto& c : l)
      if (c == 'O') count++;
  }
  fmt::print("Sum:\n{}\n", count +1);
}


