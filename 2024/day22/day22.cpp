

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
       auto change = ((char)prices[i] - (char)prev);
       auto val = change >= 0 ? ('0' + change) : ('a' - change);
       changes += val; 
       prev = prices[i];
   }
   return changes;
}

using Indexes = std::map<std::string, std::vector<unsigned>>;


auto find_indexes(const std::string& pattern, const std::string& changes, const Seeds& prices) {
      unsigned long long bananas = 0;
      for (auto i = changes.find(pattern); i != std::string::npos; i = changes.find(pattern, i + 1)) {
          bananas += prices[i + 4];
          break; // only on first seen
      }
      return bananas;
}

auto find_in_all_indexes(const std::string& pattern, const std::vector<Seeds>& all_prices, const std::vector<std::string> &all_changes) {
    unsigned long long bananas = 0;
    for (auto i = 0; i < all_prices.size(); i++) {
        bananas += find_indexes(pattern, all_changes[i], all_prices[i]);
    }
    //fmt::print("pattern {} bananas: {}\n", pattern, bananas);
    return bananas;
}

auto compute(const std::vector<Seeds>& all_prices, const std::vector<std::string> & all_changes) {

    unsigned long long best_bananas = 0;
    auto best_pattern = std::string{};

    auto indexes = Indexes{};

    for (auto &changes : all_changes) {
        for (auto i = 0; i < changes.size() -4; i++) {
            auto pattern = changes.substr(i, 4);
            if (indexes.contains(pattern)) continue;
            auto bananas = find_in_all_indexes(pattern, all_prices, all_changes);
            indexes[pattern] = {};
            if (bananas > best_bananas) {
                best_bananas = bananas;
                best_pattern = pattern;
            }
        }
    }
    return best_bananas; 
}

int main() {

  auto seeds = Seeds{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      seeds.emplace_back(stoll(input));
  }
  fmt::print("Seed are:\n{}\n", seeds);

  unsigned long long sum = 0;
  auto all_prices = std::vector<Seeds>{};
  for (auto s : seeds) {
      auto res = s;
      auto prices = Seeds{s % 10};
      for (auto it = 0; it < 2000; it++) {
          res = evolve(res, it); 
          prices.emplace_back(res % 10);
      }
      all_prices.emplace_back(prices);
      sum += res;
  }
  fmt::print("Sum is: {}\n", sum);

  auto all_changes = std::vector<std::string>{};
  for (auto &prices : all_prices) {
      //fmt::print("Prices: {}\n", prices);
      auto changes = compute_changes(prices);
      all_changes.emplace_back(changes);
      //fmt::print("changes {}\n", changes);
      //auto bana = find_indexes(changes, prices)
      //fmt::print("bana: {}\n", bana);
  }

  auto bananas = compute(all_prices, all_changes);

  fmt::print("bananas: {}\n", bananas);
}


