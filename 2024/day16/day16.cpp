

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

struct Reindeer {

  bool operator==(const Guard&) const = default;

  enum class Direction { N, E, S, O };

  Direction dir;

  Pos  pos;
};


//void move_right(Pos &robot, Map &map) {
//    auto &line = map[robot.y];
//    auto idx = robot.x + 1;
//    while (line[idx] == 'O' or line[idx] == '[' or line[idx] == ']') idx++;
//    if (line[idx] == '#') return; // blocked
//    if (line[idx] != '.') throw "WTF";
//
//    line.erase(idx, 1);
//    line.insert(robot.x + 1, 1, '.');
//    robot.x++;
//}
//
//void move_left(Pos &robot, Map &map) {
//    auto &line = map[robot.y];
//    auto idx = robot.x - 1;
//    while (line[idx] == 'O' or line[idx] == '[' or line[idx] == ']') idx--;
//    if (line[idx] == '#') return; // blocked
//    if (line[idx] != '.') throw "WTF";
//
//    line.erase(idx, 1);
//    line.insert(robot.x - 1, 1, '.');
//    robot.x--;
//}
//
//template<bool p2 = false>
//void move_up(Pos &robot, Map &map) {
//    auto col = [&map, &x = robot.x] (unsigned col) mutable -> auto & { return map[col][x]; };
//    auto idx = robot.y - 1;
//    while (col(idx) == 'O') idx--;
//    if (col(idx) == '#') return; // blocked
//    if (col(idx) != '.') throw "WTF";
//
//    col(idx) = col(robot.y - 1);
//    col(robot.y - 1) = '.';
//    robot.y--;
//}
//
//template<bool p2 = false>
//void move_down(Pos &robot, Map &map) {
//    auto col = [&map, &x = robot.x] (unsigned col) mutable -> auto & { return map[col][x]; };
//    auto idx = robot.y + 1;
//    while (col(idx) == 'O') idx++;
//    if (col(idx) == '#') return; // blocked
//    if (col(idx) != '.') throw "WTF";
//
//    col(idx) = col(robot.y + 1);
//    col(robot.y + 1) = '.';
//    robot.y++;
//}
//
//bool movable_up(int x, int y, const Map& map, std::vector<Pos>& movable) {
//
//    auto col_x_at = [&map, &x] (unsigned col) mutable -> auto & { return map[col][x]; };
//    if (col_x_at(y) == '#') return false; // blocked
//    if (col_x_at(y) == '[') {
//        movable.emplace_back(x, y);
//        return movable_up(x, y - 1, map, movable) and movable_up(x + 1, y -1, map, movable);
//    }
//    if (col_x_at(y) == ']') {
//        movable.emplace_back(x - 1, y);
//        return movable_up(x, y - 1, map, movable) and movable_up(x - 1, y -1, map, movable);
//    }
//    if (col_x_at(y) != '.') throw "WTF";
//    return true;
//}
//
//bool movable_down(int x, int y, const Map& map, std::vector<Pos>& movable) {
//
//    auto col_x_at = [&map, &x] (unsigned col) mutable -> auto & { return map[col][x]; };
//    if (col_x_at(y) == '#') return false; // blocked
//    if (col_x_at(y) == '[') {
//        movable.emplace_back(x, y);
//        return movable_down(x, y + 1, map, movable) and movable_down(x + 1, y +1, map, movable);
//    }
//    if (col_x_at(y) == ']') {
//        movable.emplace_back(x - 1, y);
//        return movable_down(x, y + 1, map, movable) and movable_down(x - 1, y +1, map, movable);
//    }
//    if (col_x_at(y) != '.') throw "WTF";
//    return true;
//}
//
//template<>
//void move_up<true>(Pos &robot, Map &map) {
//    auto movable = std::vector<Pos>{};
//    if (not movable_up(robot.x, robot.y - 1, map, movable)) return; // blocked
//
//    std::ranges::sort(movable, [](const auto &a, const auto &b) { return a.y < b.y or (a.y == b.y and a.x < b.x); });
//    for (auto &c : movable) {
//       map[c.y][c.x] = '.'; 
//       map[c.y][c.x + 1] = '.'; 
//       map[c.y - 1][c.x] = '['; 
//       map[c.y - 1][c.x + 1] = ']'; 
//    }
//    robot.y--;
//}
//
//template<>
//void move_down<true>(Pos &robot, Map &map) {
//    auto movable = std::vector<Pos>{};
//    if (not movable_down(robot.x, robot.y + 1, map, movable)) return; // blocked
//
//    std::ranges::sort(movable, [](const auto &a, const auto &b) { return a.y > b.y or (a.y == b.y and a.x < b.x); });
//    for (auto &c : movable) {
//       map[c.y][c.x] = '.'; 
//       map[c.y][c.x + 1] = '.'; 
//       map[c.y + 1][c.x] = '['; 
//       map[c.y + 1][c.x + 1] = ']'; 
//    }
//    robot.y++;
//}
//
//template<bool p2 = false>
//void move(Pos &robot, unsigned char dir, Map &map) {
//    switch(dir) {
//        case '<':
//            move_left(robot, map);
//            break;
//        case '>':
//            move_right(robot, map);
//            break;
//        case '^':
//            move_up<p2>(robot, map);
//            break;
//        case 'v':
//            move_down<p2>(robot, map);
//            break;
//    }
//}
//
//auto transform(const Map& map) {
//  auto wide_map = Map(map.size());
//  auto idx = 0;
//  for (auto &l : map) {
//     for (auto &c : l) {
//       switch (c) {
//        case '.': wide_map[idx].append(2, '.'); break;
//        case '#': wide_map[idx].append(2, '#'); break;
//        case 'O': wide_map[idx].append("[]"); break;
//       }
//     }
//     idx++;
//  }
//  return wide_map;
//}
//
auto move(Reindeer &reindeer, const Map& map, Map &path) {

  switch(reindeer.dir) {
    case Reindeer::Direction::N:
      if (reindeer.pos.y - 1 >= 0
          and map[reindeer.pos.y - 1][reindeer.pos.x] == '#') {
        reindeer.dir = Reindeer::Direction::E;
      } else {
        reindeer.pos.y--;
      }
      break;
    case Reindeer::Direction::O:
      if (reindeer.pos.x - 1 >= 0
          and map[reindeer.pos.y][reindeer.pos.x - 1] == '#') {
        reindeer.dir = Reindeer::Direction::N;
      } else {
        reindeer.pos.x--;
      }
      break;

    case Reindeer::Direction::S:
      if (reindeer.pos.y + 1 <= map.size() - 1
          and map[reindeer.pos.y + 1][reindeer.pos.x] == '#') {
        reindeer.dir = Reindeer::Direction::O;
      } else {
        reindeer.pos.y++;
      }
      break;
    case Reindeer::Direction::E:
      if (reindeer.pos.x + 1 <= map[0].size() - 1
          and map[reindeer.pos.y][reindeer.pos.x + 1] == '#') {
        reindeer.dir = Reindeer::Direction::S;
      } else {
        reindeer.pos.x++;
      }
      break;
  }

  if (reindeer.pos.x >= map[0].size()
      or reindeer.pos.x < 0
      or reindeer.pos.y >=  map.size()
      or reindeer.pos.y < 0) {
    return false;
  }

  return true;
}

std::optional<unsigned> crawl_region(int x, int y, Region& region, Map &map) {
   if (map[y][x] == '#') {
     return {};
   }
   if (map[y][x] == 'E') {
       return 0;
   }

   crawl_region(x + 1, y, region, map);
   crawl_region(x - 1, y, region, map);
   crawl_region(x, y + 1, region, map);
   crawl_region(x, y - 1, region, map);
}

int main() {

  auto reindeer = Reindeer{};
  auto map = Map{};
  auto input = std::string{};
  auto idx = 0;
  while (getline(std::cin, input)) {
      if (input.size() == 0) break;
      auto pos = input.find('S');
      if (pos != std::string::npos) {
        reindeer.pos.x = pos;
        reindeer.pos.y = idx;
        reindeer.dir = Reindeer::Direction::E;
        input[pos] = '.';
      }
      map.push_back(input);
      idx++;
  }

  fmt::print("Reindeer:\n{}\n", reindeer);
  fmt::print("Map:\n{}\n", fmt::join(map, "\n"));
}


