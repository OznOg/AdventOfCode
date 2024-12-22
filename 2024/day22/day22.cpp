

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

using Seeds = std::vector<unsigned long long>;


//    Calculate the result of multiplying the secret number by 64. Then, mix this result into the secret number. Finally, prune the secret number.
//    Calculate the result of dividing the secret number by 32. Round the result down to the nearest integer. Then, mix this result into the secret number. Finally, prune the secret number.
//    Calculate the result of multiplying the secret number by 2048. Then, mix this result into the secret number. Finally, prune the secret number.

unsigned long long evolve(unsigned long long val, unsigned iter) {
    val = (val ^ (val * 64)) % 16777216ull;
    val = ((val / 32) ^ val) % 16777216ull;
    return (val ^ (val * 2048)) % 16777216ull;
}

auto compute_changes(const Seeds& prices) {
   auto changes = std::string{};
   // all done using 'p' as 0 and other relative to 'p'
   auto prev = prices[0];
   for (auto i = 1; i < prices.size(); i++) {
       changes += 'p' + ((char)prices[i] - (char)prev); 
       prev = prices[i];
   }
   return changes;
}

using Indexes = std::map<std::string, std::vector<unsigned>>;


auto find_indexes(const std::string& all, size_t pos, Indexes& indexes) {
      auto pattern = all.substr(0, 4);
      if (indexes.contains(pattern)) return;

      for (auto i = all.find(pattern); i != std::string::npos; i = all.find(pattern, i + 1)) {
          indexes[pattern].emplace_back(i + pos); 
      }
      find_indexes(all.substr(1, std::string::npos), 1, indexes);
}

int main() {

  auto seeds = Seeds{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      seeds.emplace_back(stoll(input));
  }
  fmt::print("Seed are:\n{}\n", seeds);

  unsigned long long sum = 0;
  for (auto s : seeds) {
      auto res = s;
      auto prices = Seeds{s % 10};
      for (auto it = 0; it < 2000; it++) {
          res = evolve(res, it); 
          prices.emplace_back(res % 10);
      }
      //fmt::print("Prices: {}\n", prices);
      auto changes = compute_changes(prices);
      //fmt::print("Changes: {}\n", changes);
      //fmt::print("{}: {}\n", s, res);
      Indexes indexes;
      find_indexes(changes, 0, indexes);
      fmt::print("indexes: {}\n", indexes);

      sum += res;
  }
  fmt::print("Sum is: {}\n", sum);
}


