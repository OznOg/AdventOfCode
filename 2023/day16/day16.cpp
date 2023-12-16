#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <set>
#include <optional>
#include <list>
#include <numeric>

using Line = std::string;
using Data = std::vector<Line>;

enum class Dir {
  Up,
  Right,
  Down,
  Left
};

struct Log {
   std::pair<int, int> pos;
   Dir dir;
};
using Backlog = std::vector<Log>;

auto next(std::pair<int, int> pos, Dir dir) {
    auto &[x, y] = pos;
    switch (dir) {
        case Dir::Up:    y -= 1; break;
        case Dir::Right: x += 1; break;
        case Dir::Down:  y += 1; break;
        case Dir::Left:  x -= 1; break;
    }
    return pos;
};

void _energize(const Data &data, Data &energized, std::pair<int, int> pos, Dir dir, Backlog &log) {
   if (std::find_if(log.begin(), log.end(), [&](auto &l) { return l.pos == pos && l.dir == dir; }) == log.end()) {
       log.emplace_back(Log{pos, dir});
       if (not(pos.first == -1 && pos.second == 0)) // hack for first pos
           energized[pos.second][pos.first] = '#';
   } else {
       return; // already came here that way
   }
   
   auto new_pos = next(pos, dir);

   // beam goes outside the playground
   if (new_pos.first < 0 || new_pos.second < 0
       || new_pos.first >= data.front().size() || new_pos.second >= data.size())
     return;


   switch (data[new_pos.second][new_pos.first]) {
     case '.':
        return _energize(data, energized, new_pos, dir, log);
     case '/':
     {
         auto new_dir = [&] {
             switch (dir) {
                 case Dir::Up:    return Dir::Right;
                 case Dir::Right: return Dir::Up;
                 case Dir::Down:  return Dir::Left;
                 case Dir::Left:  return Dir::Down;
                 default: throw "WTF";
             }
         }();
         return _energize(data, energized, new_pos, new_dir, log);
     }
     break;
     case '\\':
     {
         auto new_dir = [&] {
             switch (dir) {
                 case Dir::Up:    return Dir::Left;
                 case Dir::Right: return Dir::Down;
                 case Dir::Down:  return Dir::Right;
                 case Dir::Left:  return Dir::Up;
                 default: throw "WTF";
             }
         }();
         return _energize(data, energized, new_pos, new_dir, log);
     }
     break;
     case '|':
     {
         switch (dir) {
             case Dir::Up:
             case Dir::Down:
                 return _energize(data, energized, new_pos, dir, log);

             case Dir::Right:
             case Dir::Left:
                 _energize(data, energized, new_pos, Dir::Up, log);
                 _energize(data, energized, new_pos, Dir::Down, log);
             return;
             default: throw "WTF";
         }
     }
     break;
     case '-':
     {
         switch (dir) {
             case Dir::Right:
             case Dir::Left:
                 return  _energize(data, energized, new_pos, dir, log);

             case Dir::Up:
             case Dir::Down:
                 _energize(data, energized, new_pos, Dir::Right, log);
                 _energize(data, energized, new_pos, Dir::Left, log);
             return;
             default: throw "WTF";
         }
     }
     break;
   }
   throw "WTF";
}

Data energize(const Data &data) {
  auto energized = data;
  auto pos = std::make_pair(-1, 0);
  auto dir = Dir::Right;
  auto log = Backlog{};
  _energize(data, energized, pos, dir, log);
  return energized;
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
        data.emplace_back(std::move(input));
    }

    auto energized = energize(data);

    auto count = 0u;
    for (auto &l: energized) {
        std::cout << l << '\n';
       for (auto &c : l)
          count += (c == '#');
    }
    std::cout << "Count of energized: " << count << '\n';
}


