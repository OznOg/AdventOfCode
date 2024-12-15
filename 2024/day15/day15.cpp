

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
    while (line[idx] == 'O') idx++;
    if (line[idx] == '#') return; // blocked
    if (line[idx] != '.') throw "WTF";

    line[idx] = line[robot.x + 1];
    line[robot.x + 1] = '.';
    robot.x++;
}

void move_left(Pos &robot, Map &map) {
    auto &line = map[robot.y];
    auto idx = robot.x - 1;
    while (line[idx] == 'O') idx--;
    if (line[idx] == '#') return; // blocked
    if (line[idx] != '.') throw "WTF";

    line[idx] = line[robot.x - 1];
    line[robot.x - 1] = '.';
    robot.x--;
}

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

void move(Pos &robot, unsigned char dir, Map &map) {
    switch(dir) {
        case '<':
            move_left(robot, map);
            break;
        case '>':
            move_right(robot, map);
            break;
        case '^':
            move_up(robot, map);
            break;
        case 'v':
            move_down(robot, map);
            break;
    }
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

  fmt::print("Map:\n{}\n", fmt::join(map, "\n"));

  for (auto &dir : movements) {
     move(robot, dir, map);
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


