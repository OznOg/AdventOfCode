


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <format>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
#include <list>
#include <ranges>
#include <regex>


auto expand_disk_map(const std::string& dense_disk_map) {
  auto disk_map = std::vector<std::optional<unsigned>>{};

  auto idx = 0u;
  for (auto pos = 0; pos < dense_disk_map.size(); pos += 2) {
      auto file_size = dense_disk_map[pos] - '0';
      disk_map.insert(disk_map.end(), file_size, idx);
      if (pos + 1 < dense_disk_map.size()) {
        auto free_size = dense_disk_map[pos + 1] - '0';
        disk_map.insert(disk_map.end(), free_size, {});
      }
      idx++;
  }
  
  return disk_map;
}

auto trim(const std::vector<std::optional<unsigned>>& map) {
  auto trimmed = map;
  while (!trimmed.back())
    trimmed.pop_back();
  return trimmed;
}
auto move_stuff(const std::vector<std::optional<unsigned>>& map) {
  auto move = map;

  move = trim(move);
  auto idx = 0u;
  while (idx < move.size()) {
    if (!move[idx]) {
      move[idx] = move.back();
      move.pop_back();
    }
    idx++;
    move = trim(move);
  }
  return move;
}

int main() {

  auto dense_disk_map = std::string{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
    dense_disk_map = input;
  }

  //fmt::print("Dense disk map: {}\n", dense_disk_map);
  auto disk_map = expand_disk_map(dense_disk_map);
  //fmt::print("Disk map: {}\n", disk_map);
  
  auto moved = move_stuff(disk_map);
  //fmt::print("Moved map: {}\n", fmt::join(moved, ""));


  unsigned long long sum{};

  unsigned long long idx{};
  for (auto &e : moved) {
    sum += idx * e.value();
    idx++;
  }
  
  fmt::print("Sum: {}\n", sum);
}

