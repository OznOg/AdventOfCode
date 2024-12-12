

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


int main() {

  auto input = std::string{};
  auto first = true;
  while (getline(std::cin, input)) {
      if (first) {
        map.push_back(std::string(input.size() + 2, ' '));
        first = false;
      }
      map.push_back(' ' + input + ' ');
  }
  map.push_back(std::string(map[0].size(), ' '));

  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));
  
}

