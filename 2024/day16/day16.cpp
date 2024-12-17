

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
  
  enum class Direction { N, E, S, O };

  bool operator==(const Reindeer&) const = default;

  Direction dir;

  Pos  pos;

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
using History = std::map<unsigned long long, std::map<unsigned, std::map<Reindeer::Direction, unsigned>>>;

//auto move(Reindeer &reindeer, const Map& map, unsigned long long cost, History &history) {
//
//  if (history[reindeer.pos.y][reindeer.pos.x]) {
//    return history[reindeer.pos.y][reindeer.pos.x];
//  }
//  switch(reindeer.dir) {
//    case Reindeer::Direction::N:
//      {
//        history[reindeer.pos.y][reindeer.pos.x] = static_cast<unsigned long long>(-1);
//        for (auto dir : {Reindeer::Direction::E, Reindeer::Direction::W}) {
//          reindeer.dir = dir;
//          auto new_cost = move(reindeer, map, cost + 1000, history);
//          history[reindeer.pos.y][reindeer.pos.x] = new_cost.value_or(history[reindeer.pos.y][reindeer.pos.x]);
//
//        }
//        if (map[reindeer.pos.y - 1][reindeer.pos.x] != '#') {
//          reindeer.pos.y--;
//          auto new_cost = move(reindeer, map, cost + 1, history);
//          history[reindeer.pos.y][reindeer.pos.x] = new_cost.value_or(history[reindeer.pos.y][reindeer.pos.x]);
//        }
//      }
//      break;
//    case Reindeer::Direction::O:
//      if (reindeer.pos.x - 1 >= 0
//          and map[reindeer.pos.y][reindeer.pos.x - 1] == '#') {
//        reindeer.dir = Reindeer::Direction::N;
//      } else {
//        reindeer.pos.x--;
//      }
//      break;
//
//    case Reindeer::Direction::S:
//      if (reindeer.pos.y + 1 <= map.size() - 1
//          and map[reindeer.pos.y + 1][reindeer.pos.x] == '#') {
//        reindeer.dir = Reindeer::Direction::O;
//      } else {
//        reindeer.pos.y++;
//      }
//      break;
//    case Reindeer::Direction::E:
//      if (reindeer.pos.x + 1 <= map[0].size() - 1
//          and map[reindeer.pos.y][reindeer.pos.x + 1] == '#') {
//        reindeer.dir = Reindeer::Direction::S;
//      } else {
//        reindeer.pos.x++;
//      }
//      break;
//  }
//
//  if (reindeer.pos.x >= map[0].size()
//      or reindeer.pos.x < 0
//      or reindeer.pos.y >=  map.size()
//      or reindeer.pos.y < 0) {
//    return false;
//  }
//
//  return true;
//}

std::vector<unsigned> sc;

std::vector<Reindeer> crawl_region(Reindeer &r, Map &map, History& history) {

    auto next = std::vector<Reindeer>{};

    if (map[r.pos.y][r.pos.x] == 'E') {
       fmt::print("===============>{}\n", r.score);
       history[r.pos.y][r.pos.x][r.dir] = r.score;
       sc.push_back(r.score);
       return {};
    }
    switch(r.dir) {
        case Reindeer::Direction::N:
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            } 
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.pos.x--;
                rn.dir = Reindeer::Direction::O;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            break;

        case Reindeer::Direction::O:
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.pos.x--;
                rn.dir = Reindeer::Direction::O;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            break;

        case Reindeer::Direction::S:
            if (map[r.pos.y][r.pos.x - 1] != '#') {
                auto rn = r;
                rn.dir = Reindeer::Direction::O;
                rn.pos.x--;
                rn.score += 1001;
                rn.dir = Reindeer::Direction::O;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            } 
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            break;

        case Reindeer::Direction::E:
            if (map[r.pos.y + 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y++;
                rn.dir = Reindeer::Direction::S;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y][r.pos.x + 1] != '#') {
                auto rn = r;
                rn.pos.x++;
                rn.dir = Reindeer::Direction::E;
                rn.score += 1;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
            }
            if (map[r.pos.y - 1][r.pos.x] != '#') {
                auto rn = r;
                rn.pos.y--;
                rn.dir = Reindeer::Direction::N;
                rn.score += 1001;
                if (!history[rn.pos.y][rn.pos.x][rn.dir] or history[rn.pos.y][rn.pos.x][rn.dir] > rn.score)
                    next.emplace_back(rn);
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

  fmt::print("Sc:\n{}\n", std::ranges::min(sc));
  fmt::print("History:\n{}\n", fmt::join(h, "\n"));
}


