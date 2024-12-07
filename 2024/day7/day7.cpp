


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cmath>
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


auto exp10(unsigned long long x, unsigned pow) {
    unsigned long long res = 1;
    for (auto i = 0; i < pow; i++) {
       res *= x;
    }
    return res;
}

template <bool p2 = false>
auto check(const Equation& e) -> bool {
    if (e.numbers.empty()) return false;

    auto rem = e;
    auto v = rem.numbers.back();
    rem.numbers.pop_back();
    if ((rem.value % v) == 0) {
       rem.value /= v;
       if (rem.value == 1 && rem.numbers.empty()) return true;
       if (check<p2>(rem)) {
           return true;
       }
       rem.value *= v;
    }
    if (rem.value >= v) {
       rem.value -= v;
       if (rem.value == 0 && rem.numbers.empty()) return true;
       if (check<p2>(rem)) {
           return true;
       }
       rem.value += v;
    }

    if constexpr (p2) {
        auto size = static_cast<long>(std::log10(v) + 1);
        if ((rem.value % exp10(10, size)) == v) {
            rem.value = rem.value / (exp10(10, size));
            return check<p2>(rem);
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
      eq.value = std::stoll(input.substr(0, pos));

      auto ss = std::stringstream{input.substr(pos + 1, std::string::npos)};
      unsigned val;
      while (ss >> val) {
         eq.numbers.push_back(val);
      }
      data.push_back(eq);
  }


  { //p1
      unsigned long long sum = 0u;
      for (auto &e : data) {
          if (check<>(e)) {
              sum += e.value;
          }
      }

      fmt::print("Sum is: {}\n", sum);
  }

  { //p2
      unsigned long long sum = 0u;
      for (auto &e : data) {
          if (check<true>(e)) {
              sum += e.value;
          }
      }

      fmt::print("Sum is: {}\n", sum);
  }
}

