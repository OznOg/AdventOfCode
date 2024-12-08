


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <format>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include <regex>


using Map = std::vector<std::string>;

struct Guard {

  bool operator==(const Guard&) const = default;

  enum class Direction { N, E, S, O };

  Direction dir;

  struct Pos { 
    bool operator==(const Pos&) const = default;
    int x, y;
  } pos;
};



auto move(Guard &guard, const Map& map, Map &path) {
  path[guard.pos.y][guard.pos.x] = 'X';

  switch(guard.dir) {
    case Guard::Direction::N:
      if (guard.pos.y - 1 >= 0
          and map[guard.pos.y - 1][guard.pos.x] == '#') {
        guard.dir = Guard::Direction::E;
      } else {
        guard.pos.y--;
      }
      break;
    case Guard::Direction::O:
      if (guard.pos.x - 1 >= 0
          and map[guard.pos.y][guard.pos.x - 1] == '#') {
        guard.dir = Guard::Direction::N;
      } else {
        guard.pos.x--;
      }
      break;

    case Guard::Direction::S:
      if (guard.pos.y + 1 <= map.size() - 1
          and map[guard.pos.y + 1][guard.pos.x] == '#') {
        guard.dir = Guard::Direction::O;
      } else {
        guard.pos.y++;
      }
      break;
    case Guard::Direction::E:
      if (guard.pos.x + 1 <= map[0].size() - 1
          and map[guard.pos.y][guard.pos.x + 1] == '#') {
        guard.dir = Guard::Direction::S;
      } else {
        guard.pos.x++;
      }
      break;
  }

  if (guard.pos.x >= map[0].size()
      or guard.pos.x < 0
      or guard.pos.y >=  map.size()
      or guard.pos.y < 0) {
    return false;
  }

  return true;
}

int main() {

  auto map = Map{};
  auto path = Map{};
  auto guard = Guard{};
  auto idx = 0u;
  auto input = std::string{};
  while (getline(std::cin, input)) {
    auto it = std::ranges::find_if(input, [] (auto &c) { return c != '.' and c != '#'; });
    if (it != input.end()) {
      guard.pos.y = idx;
      guard.pos.x = it - input.begin();

      switch(*it) {
        case '^': guard.dir = Guard::Direction::N; break;
        case '>': guard.dir = Guard::Direction::E; break;
        case 'v': guard.dir = Guard::Direction::S; break;
        case '<': guard.dir = Guard::Direction::O; break;
      }

      *it = '.';
    }
    map.push_back(input);
    path.emplace_back(input.size(), ' ');
    idx++;
  }


  fmt::print("Map\n{}\n", fmt::join(map, "\n"));

  { // p1
    auto g = guard;
    while (move(g, map, path)) {
      //  fmt::print("Path\n{}\n", fmt::join(path, "\n"));
      ;
    }

    fmt::print("Path\n{}\n", fmt::join(path, "\n"));

    auto count = 0u;
    for (auto &c : fmt::format("{}", fmt::join(path, ""))) {
      if (c == 'X') count++;
    }

    fmt::print("count is: {}\n", count);
  }
  { //p2

    auto count = 0u;
    for (auto j = 0; j < map.size(); j++) {
      fmt::print("Testing line {}\n", j);
      for (auto i = 0; i < map[0].size(); i++) {
        if (map[j][i] == '#') continue;

        auto g = guard;
        auto temp = map;
        temp[j][i] = '#';

        auto history = std::vector<std::vector<std::set<Guard::Direction>>>(map.size());
        for (auto &l : history) {
            l.resize(map[0].size());
        }

        //fmt::print("Testing\n{}\n", fmt::join(temp, "\n"));
        history[g.pos.y][g.pos.x].insert(g.dir);
        while (move(g, temp, path)) {
          if (history[g.pos.y][g.pos.x].contains(g.dir)) {
            count++;
            break;
          }
          history[g.pos.y][g.pos.x].insert(g.dir);
        }
        temp[j][i] = '.';
      }
    }
    fmt::print("count is: {}\n", count);
  }
}

