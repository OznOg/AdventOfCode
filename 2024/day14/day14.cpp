

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

struct Robot {
    struct Velocity {
        long long x, y;
    } v;
 
    Pos pos;

    friend auto format_as(const Robot &r) {
        return fmt::format("Robot: pos={} v=({}, {})", r.pos, r.v.x, r.v.y);
    }
};

using Map = std::vector<std::vector<unsigned>>;


void move(Robot& robot, size_t seconds, Map& map) {
    robot.pos.x += robot.v.x * seconds;
    robot.pos.y += robot.v.y * seconds;
    robot.pos.x %= map.front().size();
    robot.pos.y %= map.size();
}

void move(std::vector<Robot>& robots, size_t seconds, Map &map) {
    std::ranges::for_each(robots, [seconds, &map](auto &r) { move(r, seconds, map); });
}

int main() {

  auto robots = std::vector<Robot>{};
  auto input = std::string{};
  std::regex r(R"(p=(\d+),(\d+) v=([^,]+),([^,]+)$)");
  while (getline(std::cin, input)) {
      auto robot = Robot{};
      std::smatch sm;
      regex_search(input, sm, r);
      robot.pos.x = stol(sm[1].str());
      robot.pos.y = stol(sm[2].str());
      robot.v.x = stol(sm[3].str());
      robot.v.y = stol(sm[4].str());
      
      robots.push_back(robot);
  }

  fmt::print("Robots are:\n{}\n", fmt::join(robots, "\n"));

  auto map = Map{};
  if (robots.size() <= 12) {
     map.resize(7);
     std::ranges::for_each(map, [] (auto &s) { s.resize(11); });
  } else {
     map.resize(103);
     std::ranges::for_each(map, [] (auto &s) { s.resize(101); });
  }
  
  std::ranges::for_each(robots, [&map](auto &r) { 
     // adjust speed to be positive
     while (r.v.x < 0) {
       r.v.x += 1000 * map.front().size();
       r.v.x %= map.front().size();
     }

     while (r.v.y < 0) {
       r.v.y += 1000 * map.size();
       r.v.y %= map.size();
     }
     });

  auto seconds = 100;
  move(robots, seconds, map);
  fmt::print("Robots are:\n{}\n", fmt::join(robots, "\n"));
  
  std::ranges::for_each(robots, [&map](auto &r) { 
     map[r.pos.y][r.pos.x]++;
  });
  fmt::print("MAp:\n{}\n", fmt::join(map, "\n"));


  auto q1 = 0u;
  auto q2 = 0u;
  auto q3 = 0u;
  auto q4 = 0u;
  
  for (auto y = 0; y < map.size() / 2; y++) {
      for (auto x = 0; x < map.front().size() / 2; x++) {
          q1 += map[y][x];
      }
  }
  for (auto y = map.size() / 2 + 1; y < map.size(); y++) {
      for (auto x = 0; x < map.front().size() / 2; x++) {
          q2 += map[y][x];
      }
  }
  for (auto y = 0; y < map.size() / 2; y++) {
      for (auto x = map.front().size() / 2 + 1; x < map.front().size(); x++) {
          q3 += map[y][x];
      }
  }
  for (auto y = map.size() / 2 + 1; y < map.size(); y++) {
      for (auto x = map.front().size() / 2 + 1; x < map.front().size(); x++) {
          q4 += map[y][x];
      }
  }
  fmt::print("{} {} {} {}\n", q1, q2, q3, q4);
  fmt::print("Safety factor is: {}\n", q1 * q2 * q3 *q4);
}


