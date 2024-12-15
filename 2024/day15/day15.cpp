

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

void move_right(Pos &robot, Map &map) {
    auto &line = map[robot.y];
    auto idx = robot.x + 1;
    while (line[idx] == 'O' or line[idx] == '[' or line[idx] == ']') idx++;
    if (line[idx] == '#') return; // blocked
    if (line[idx] != '.') throw "WTF";

    line.erase(idx, 1);
    line.insert(robot.x + 1, 1, '.');
    robot.x++;
}

void move_left(Pos &robot, Map &map) {
    auto &line = map[robot.y];
    auto idx = robot.x - 1;
    while (line[idx] == 'O' or line[idx] == '[' or line[idx] == ']') idx--;
    if (line[idx] == '#') return; // blocked
    if (line[idx] != '.') throw "WTF";

    line.erase(idx, 1);
    line.insert(robot.x - 1, 1, '.');
    robot.x--;
}

template<bool p2 = false>
void move_up(Pos &robot, Map &map) {
    auto col = [&map, &x = robot.x] (unsigned col) mutable -> auto & { return map[col][x]; };
    auto idx = robot.y - 1;
    while (col(idx) == 'O') idx--;
    if (col(idx) == '#') return; // blocked
    if (col(idx) != '.') throw "WTF";

    col(idx) = col(robot.y - 1);
    col(robot.y - 1) = '.';
    robot.y--;
}

template<bool p2 = false>
void move_down(Pos &robot, Map &map) {
    auto col = [&map, &x = robot.x] (unsigned col) mutable -> auto & { return map[col][x]; };
    auto idx = robot.y + 1;
    while (col(idx) == 'O') idx++;
    if (col(idx) == '#') return; // blocked
    if (col(idx) != '.') throw "WTF";

    col(idx) = col(robot.y + 1);
    col(robot.y + 1) = '.';
    robot.y++;
}

bool movable_up(int x, int y, const Map& map, std::vector<Pos>& movable) {

    auto col_x_at = [&map, &x] (unsigned col) mutable -> auto & { return map[col][x]; };
    if (col_x_at(y) == '#') return false; // blocked
    if (col_x_at(y) == '[') {
        movable.emplace_back(x, y);
        return movable_up(x, y - 1, map, movable) and movable_up(x + 1, y -1, map, movable);
    }
    if (col_x_at(y) == ']') {
        movable.emplace_back(x - 1, y);
        return movable_up(x, y - 1, map, movable) and movable_up(x - 1, y -1, map, movable);
    }
    if (col_x_at(y) != '.') throw "WTF";
    return true;
}

bool movable_down(int x, int y, const Map& map, std::vector<Pos>& movable) {

    auto col_x_at = [&map, &x] (unsigned col) mutable -> auto & { return map[col][x]; };
    if (col_x_at(y) == '#') return false; // blocked
    if (col_x_at(y) == '[') {
        movable.emplace_back(x, y);
        return movable_down(x, y + 1, map, movable) and movable_down(x + 1, y +1, map, movable);
    }
    if (col_x_at(y) == ']') {
        movable.emplace_back(x - 1, y);
        return movable_down(x, y + 1, map, movable) and movable_down(x - 1, y +1, map, movable);
    }
    if (col_x_at(y) != '.') throw "WTF";
    return true;
}

template<>
void move_up<true>(Pos &robot, Map &map) {
    auto movable = std::vector<Pos>{};
    if (not movable_up(robot.x, robot.y - 1, map, movable)) return; // blocked

    std::ranges::sort(movable, [](const auto &a, const auto &b) { return a.y < b.y or (a.y == b.y and a.x < b.x); });
    for (auto &c : movable) {
       map[c.y][c.x] = '.'; 
       map[c.y][c.x + 1] = '.'; 
       map[c.y - 1][c.x] = '['; 
       map[c.y - 1][c.x + 1] = ']'; 
    }
    robot.y--;
}

template<>
void move_down<true>(Pos &robot, Map &map) {
    auto movable = std::vector<Pos>{};
    if (not movable_down(robot.x, robot.y + 1, map, movable)) return; // blocked

    std::ranges::sort(movable, [](const auto &a, const auto &b) { return a.y > b.y or (a.y == b.y and a.x < b.x); });
    for (auto &c : movable) {
       map[c.y][c.x] = '.'; 
       map[c.y][c.x + 1] = '.'; 
       map[c.y + 1][c.x] = '['; 
       map[c.y + 1][c.x + 1] = ']'; 
    }
    robot.y++;
}

template<bool p2 = false>
void move(Pos &robot, unsigned char dir, Map &map) {
    switch(dir) {
        case '<':
            move_left(robot, map);
            break;
        case '>':
            move_right(robot, map);
            break;
        case '^':
            move_up<p2>(robot, map);
            break;
        case 'v':
            move_down<p2>(robot, map);
            break;
    }
}

auto transform(const Map& map) {
  auto wide_map = Map(map.size());
  auto idx = 0;
  for (auto &l : map) {
     for (auto &c : l) {
       switch (c) {
        case '.': wide_map[idx].append(2, '.'); break;
        case '#': wide_map[idx].append(2, '#'); break;
        case 'O': wide_map[idx].append("[]"); break;
       }
     }
     idx++;
  }
  return wide_map;
}

int main() {

  auto robot = Pos{};
  auto map = Map{};
  auto input = std::string{};
  auto idx = 0;
  while (getline(std::cin, input)) {
      if (input.size() == 0) break;
      auto pos = input.find('@');
      if (pos != std::string::npos) {
        robot.x = pos;
        robot.y = idx;
        input[pos] = '.';
      }
      map.push_back(input);
      idx++;
  }

  auto movements = std::string{};
  while (getline(std::cin, input)) {
      movements += input;
  }
  auto wide_map = transform(map);
  auto wide_robot = robot;
  wide_robot.x *= 2;

  { // p1
      for (auto &dir : movements) {
          move<false>(robot, dir, map);
      }
      fmt::print("Robot:\n{}\n", robot);
      fmt::print("Map:\n{}\n", fmt::join(map, "\n"));

      unsigned long long sum = 0;
      for (auto y = 0u; y < map.size(); y++) {
          for (auto x = 0u; x < map.front().size(); x++) {
              if (map[y][x] == 'O') sum += 100 * y + x;
          }
      }
      fmt::print("Sum is: {}\n", sum);
  }

  { // p2
      for (auto &dir : movements) {
          move<true>(wide_robot, dir, wide_map);
      }
      fmt::print("Robot:\n{}\n", wide_robot);
      fmt::print("Map:\n{}\n", fmt::join(wide_map, "\n"));

      unsigned long long sum = 0;
      for (auto y = 0u; y < wide_map.size(); y++) {
          for (auto x = 0u; x < wide_map.front().size(); x++) {
              if (wide_map[y][x] == '[') sum += 100 * y + x;
          }
      }
      fmt::print("Sum is: {}\n", sum);
  }
}


