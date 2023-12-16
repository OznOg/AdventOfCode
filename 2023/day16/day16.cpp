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
   // beam goes outside the playground
   if (pos.first < 0 || pos.second < 0
       || pos.first >= data.front().size() || pos.second >= data.size())
     return;

   if (std::find_if(log.begin(), log.end(), [&](auto &l) { return l.pos == pos && l.dir == dir; }) == log.end()) {
       log.emplace_back(Log{pos, dir});
       energized[pos.second][pos.first] = '#';
   } else {
       return; // already came here that way
   }

   switch (data[pos.second][pos.first]) {
     case '.':
        return _energize(data, energized, next(pos, dir), dir, log);
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
         return _energize(data, energized, next(pos, new_dir), new_dir, log);
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
         return _energize(data, energized, next(pos, new_dir), new_dir, log);
     }
     break;
     case '|':
     {
         switch (dir) {
             case Dir::Up:
             case Dir::Down:
                 return _energize(data, energized, next(pos, dir), dir, log);

             case Dir::Right:
             case Dir::Left:
                 _energize(data, energized, next(pos, Dir::Up), Dir::Up, log);
                 _energize(data, energized, next(pos, Dir::Down), Dir::Down, log);
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
                 return  _energize(data, energized, next(pos, dir), dir, log);

             case Dir::Up:
             case Dir::Down:
                 _energize(data, energized, next(pos, Dir::Right), Dir::Right, log);
                 _energize(data, energized, next(pos, Dir::Left), Dir::Left, log);
             return;
             default: throw "WTF";
         }
     }
     break;
   }
   throw "WTF";
}

Data energize_at(const Data &data, std::pair<int, int> pos, Dir dir) {
  auto energized = data;
  auto log = Backlog{};
  _energize(data, energized, pos, dir, log);
  return energized;
}

auto compute_energy(const Data &energized) {
    auto count = 0u;
    for (auto &l: energized) {
  //      std::cout << l << '\n';
       for (auto &c : l)
          count += (c == '#');
    }
    return count;
}

auto best_energize(const Data &data) {
  if (data.size() != data.front().size())
    throw "WTF";

  auto all_counts = std::vector<std::pair<Log, unsigned>>{};
  for (auto i = 0; i < data.size() - 1; i++) {
      {
          auto log = Log{{i, 0}, Dir::Down};
          auto energized = energize_at(data, log.pos, log.dir);
          all_counts.emplace_back(std::make_pair(log, compute_energy(energized)));
      }
      {
          auto log = Log{{0, i}, Dir::Right};
          auto energized = energize_at(data, log.pos, log.dir);
          all_counts.emplace_back(std::make_pair(log, compute_energy(energized)));
      }
      {
          auto log = Log{{i, data.size() - 1}, Dir::Up};
          auto energized = energize_at(data, log.pos, log.dir);
          all_counts.emplace_back(std::make_pair(log, compute_energy(energized)));
      }
      {
          auto log = Log{{data.size() - 1, i}, Dir::Left};
          auto energized = energize_at(data, log.pos, log.dir);
          all_counts.emplace_back(std::make_pair(log, compute_energy(energized)));
      }
  }

  return *std::max_element(all_counts.begin(), all_counts.end(), [&](auto &&l, auto &&r) { return l.second < r.second; });
}

Data energize(const Data &data) {
    return energize_at(data, {0, 0}, Dir::Right);
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

    auto best = best_energize(data);
    std::cout << "Best count of energized: " << best.second << " " << " x=" << best.first.pos.first << " y=" << best.first.pos.second << '\n';
}


