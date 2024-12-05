


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
#include <ranges>
#include <regex>

using Rules = std::map<unsigned, std::vector<unsigned>>;
using Update = std::vector<unsigned>;
using Updates = std::vector<Update>;


bool update_match_rule(const Update &update, const unsigned& first, const std::vector<unsigned>& list) {
   auto it = std::ranges::find(update, first);
   if (it == update.end()) {
     return true;
   }

   auto res = true;
   for (const auto &e : list) {
      if (std::find(begin(update), it, e) != it) {
       // fmt::print("{} fails rule {}|{}\n", update, first, e);
        res = false;
      }
   }

   return res;
}

bool update_match_rules(const Update &update, const Rules& rules) {
  for (auto &[first, list] : rules) {
    if (not update_match_rule(update, first, list)) {
      return false;
    }
  }
  return true;
}

auto filter(const Updates &updates, const Rules& rules) {
  Updates filtered;

  for (auto &u : updates) {
    if (update_match_rules(u, rules)) {
      filtered.push_back(u);
    }
  }

  return filtered;
}

auto filter_bad(const Updates &updates, const Rules& rules) {
  Updates filtered;

  for (auto &u : updates) {
    if (not update_match_rules(u, rules)) {
      filtered.push_back(u);
    }
  }

  return filtered;
}


bool is_after_another(unsigned e, const std::set<unsigned>& update, const Rules& rules) {
  for (auto &[first, list] : rules) {
    if (not update.contains(first)) continue;

    for (auto v : list) {
      if (v == e) {
        return true;
      }
    }
  }
  return false;
}

auto fix_update(const Update &bad, const Rules& rules) {
  auto b = std::set(bad.begin(), bad.end());

  auto fixed = Update{};
  while (not b.empty()) {
    for (auto e : b) {
      if (not is_after_another(e, b, rules)) {
        fixed.push_back(e);
        b.erase(e);
        break;
      }
    }
  }
  return fixed;
}

auto fix_updates(const Updates &updates, const Rules& rules) {
  Updates all_fixed;
  
  for (auto &update : updates) {
    auto fixed = fix_update(update, rules);
    all_fixed.push_back(fixed);
  }

  return all_fixed;
}

int main() {

    auto input = std::string{};
    auto rules = Rules{};

    while (getline(std::cin, input) and not input.empty()) {
        auto pos = input.find('|');
        auto X = input.substr(0, pos);
        auto Y = input.substr(pos + 1, std::string::npos);
        rules[stol(X)].emplace_back(stol(Y));
    }

    auto updates = Updates{};
    std::regex r(R"(([^,]+,?))");
    while (getline(std::cin, input)) {
            auto update = Update{};
            for (std::smatch sm; regex_search(input, sm, r);)
            {
                update.push_back(stol(sm[1].str()));
                input = sm.suffix();
            }
            updates.push_back(update);
    }

{ // p1
    fmt::print("updates: {}\n", updates);

    auto filtered = filter(updates, rules);

    auto sum = unsigned{};
    for (auto &u : filtered) {
      sum += u[(u.size() ) / 2];
    }

    fmt::print("sum is {}\n", sum);
    }
    { //p2

    auto bad = filter_bad(updates, rules);

   fmt::print("bad is {}\n", bad);


   auto fixed = fix_updates(bad, rules);
   fmt::print("good is {}\n", fixed);
    
    auto sum = unsigned{};
    for (auto &u : fixed) {
      sum += u[(u.size() ) / 2];
    }

    fmt::print("sum is {}\n", sum);
   }

}

