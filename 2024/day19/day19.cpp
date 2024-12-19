

#include <fmt/format.h>
#include <fmt/ostream.h>
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

// from https://github.com/faheel/BigInt
#include <BigInt.hpp>

using Patterns = std::map<unsigned char, std::set<std::string>>;
using Towels = std::vector<std::string>;

using History = std::map<std::string, BigInt>;

BigInt arrange(const std::string& towel, const Patterns& patterns, History& h) {
  if (towel.size() == 0) return 1;

  if (h.contains(towel)) {
    return h[towel];
  }

  if (not patterns.contains(towel[0])) {
    h[towel] = 0;
    return 0;
  }

  auto &s = patterns.at(towel[0]); 
  auto count = BigInt(0);
  for (auto p : s) {
    if (not towel.starts_with(p)) continue;
    count += arrange(towel.substr(p.size(), std::string::npos), patterns, h);
  }
  
  h[towel] = count;
  return count; 
}

int main() {

  auto patterns = Patterns{};
  auto towels = Towels{};
  auto input = std::string{};
  std::regex r(R"( ?([^,]+))");
  std::smatch sm;
  getline(std::cin, input);
  
  for (std::smatch sm; regex_search(input, sm, r);) {
    patterns[sm[1].str()[0]].insert(sm[1]);
    input = sm.suffix();
  }

  // empty line
  getline(std::cin, input);

  while (getline(std::cin, input)) {
      towels.emplace_back(input);
  }
  fmt::print("patterns is:\n{}\n", patterns);
  fmt::print("Towels is:\n{}\n", towels);

  auto sum = BigInt(0);
  History h;
  for (auto &t : towels) {
     //fmt::print("Testing towel {}\n", t);
     auto count = arrange(t, patterns, h);
     fmt::print("Towel {} is {} : sum={}\n", t, fmt::streamed(count), fmt::streamed(sum));
     sum += count; 
  }

  fmt::print("Count is: {}\n", fmt::streamed(sum));
}


