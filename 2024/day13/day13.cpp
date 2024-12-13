

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


    double Py = machine.prize.y;
    double Px = machine.prize.x;
    double ax = machine.A.x;
    double ay = machine.A.y;
    double bx = machine.B.x;
    double by = machine.B.y;
    //Px = ax * n + bx * m;
    //Py = ay * n + by * m;

    //n = (Px - bx * m) / ax

    //Py = ay * (Px - bx * m) / ax + by * m;
    //Py = ay/ax * Px - ay/ax * bx * m + by * m;
    //Py = ay/ax * Px + (by - ay/ax * bx) * m;

    double m = (Py - (ay / ax) * Px) / (by - (ay/ax) * bx);
    double n = (Px - bx * m) / ax;

    //fmt::print("m={} n={} c={}, {} {}\n", m, n, 3 * n + m, ax * n + bx * m, ay * n + by * m);

    auto intm = std::llround(m);
    auto intn = std::llround(n);
    if (machine.prize.x == machine.A.x * intn + machine.B.x * intm
        and machine.prize.y == machine.A.y * intn + machine.B.y * intm) {
        return intm + intn * 3;
    }
    return {};
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
  

 { // p1
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
 { // p2
     unsigned long long sum = 0;
     for (auto &m : machines) {
         auto pos = Pos{};
         History h;
         m.prize.x += 10000000000000;
         m.prize.y += 10000000000000;
         auto opt = play(m, 0, pos, h);
         sum += opt.value_or(0);
     }
     fmt::print("Sum is= {}\n", sum);
}
}

