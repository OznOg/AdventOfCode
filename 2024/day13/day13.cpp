

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

struct Machine {
    struct Button {
        long long x, y;
    } A, B;
 
    Pos prize;

    friend auto format_as(const Machine &m) {
        return fmt::format("Button A: X+{}, Y+{}\n", m.A.x, m.A.y)
            + fmt::format("Button B: X+{}, Y+{}\n", m.B.x, m.B.y)
        + fmt::format("Prize: {}\n", m.prize);
    }
};


using History = std::map<unsigned, std::map<unsigned, std::optional<std::optional<size_t>>>>;
std::optional<size_t> play(const Machine &machine, const size_t curr_token, Pos pos, History& h) {

    if (h[pos.x][pos.y]) {
        return *h[pos.x][pos.y];
    }
    
    if (pos.x > machine.prize.x
       or pos.y > machine.prize.y) {
       h[pos.x][pos.y] = std::nullopt;
       return {};
    }
    
    if (pos.x == machine.prize.x
       and pos.y == machine.prize.y) {
       h[pos.x][pos.y] = curr_token;
       return curr_token;
    }

    auto posA = pos;
    posA.x += machine.A.x;
    posA.y += machine.A.y;
    auto withA = play(machine, curr_token + 3, posA, h);

    auto posB = pos;
    posB.x += machine.B.x;
    posB.y += machine.B.y;
    auto withB = play(machine, curr_token + 1, posB, h);

    auto res = withA;

    if (withB) {
     if (!res or *res > *withB) res = withB;
    }
    h[pos.x][pos.y] = res;
    return res;
}

int main() {

  auto machines = std::vector<Machine>{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      auto machine = Machine{};
      std::regex r(R"([^:]+: X[\+=]([^,]+), Y[\+=]([0-9]+))");
      std::smatch sm;
      regex_search(input, sm, r);
      machine.A.x = stol(sm[1].str());
      machine.A.y = stol(sm[2].str());
      
      getline(std::cin, input);
      regex_search(input, sm, r);
      machine.B.x = stol(sm[1].str());
      machine.B.y = stol(sm[2].str());
      
      getline(std::cin, input);
      regex_search(input, sm, r);

      machine.prize.x = stol(sm[1].str());
      machine.prize.y = stol(sm[2].str());
      
      // eat empty line
      getline(std::cin, input);
      machines.push_back(machine);
  }

  fmt::print("Map is:\n{}\n", fmt::join(machines, "\n"));
  

  unsigned long long sum = 0;
  for (auto &m : machines) {
    auto pos = Pos{};
    History h;
    auto opt = play(m, 0, pos, h);
    //fmt::print("Play= {}\n", opt);
    sum += opt.value_or(0);
  }
  fmt::print("Sum is= {}\n", sum);
  
}

