

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



using Patterns = std::map<unsigned char, std::set<std::string>>;
using Towels = std::vector<std::string>;

bool arrange(const std::string& towel, const Patterns& patterns) {
  if (towel.size() == 0) return true;

  if (not patterns.contains(towel[0])) return false;

  auto &s = patterns.at(towel[0]); 
  for (auto p : s) {
    if (not towel.starts_with(p)) continue;
    auto good = arrange(towel.substr(p.size(), std::string::npos), patterns);
    if (good)
      return good;
  }
  return false; 
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

  unsigned long long count = 0u;
  for (auto &t : towels) {
     auto good = arrange(t, patterns);
     fmt::print("Towel {} is {}\n", t, good);
     if (good) count++; 
  }
  fmt::print("Count is: {}\n", count);
}


