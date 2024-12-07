


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
#include <list>
#include <ranges>
#include <regex>


struct Equation {
 unsigned long long value;
 std::vector<unsigned long long> numbers;

 friend auto format_as(const Equation& e) {
  return fmt::format("[{}: {}]", e.value, e.numbers);
 }
};

using Data = std::vector<Equation>;



auto check(const Equation& e) -> bool {
    if (e.numbers.empty()) return false;

    auto rem = e;
    auto v = rem.numbers.back();
    rem.numbers.pop_back();
    if ((rem.value % v) == 0) {
       rem.value /= v;
       if (rem.value == 1 && rem.numbers.empty()) return true;
       if (check(rem)) {
           return true;
       }
       rem.value *= v;
    }
    if (rem.value >= v) {
       rem.value -= v;
       if (rem.value == 0 && rem.numbers.empty()) return true;
       if (check(rem)) {
           return true;
       }
    }
    return false;
}

int main() {

  auto data = std::vector<Equation>{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      auto eq = Equation{};
      auto pos = input.find(':');
      eq.value = std::stol(input.substr(0, pos));

      auto ss = std::stringstream{input.substr(pos + 1, std::string::npos)};
      unsigned val;
      while (ss >> val) {
         eq.numbers.push_back(val);
      }
      data.push_back(eq);
  }


  unsigned long long sum = 0u;
  for (auto &e : data) {
     if (check(e)) {
       sum += e.value;
     }
     else
  }

  fmt::print("Sum is: {}\n", sum);

}

