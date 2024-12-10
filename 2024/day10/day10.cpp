


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


using RawData = std::vector<std::string>;

struct POI {
   int x, y;
   friend auto format_as(const POI& poi) {
       return fmt::format("({}, {})", poi.x, poi.y);
   }
   unsigned count = 0;
};


auto find_ends(const RawData& data) {
    auto heads = std::vector<POI>{};
    auto ends = std::vector<POI>{};
    for (auto raw = 0; raw < data.size(); raw++) {
        for (auto col = 0; col < data[raw].size(); col++) {
           if (data[raw][col] == '0') {
               heads.emplace_back(col, raw);
           }
           if (data[raw][col] == '9') {
               ends.emplace_back(col, raw);
           }
        }
    }
    return std::make_pair(heads, ends);
}

template <bool p2>
auto score(int x, int y, int val, std::vector<POI>& ends, RawData& data) {
   if (val == '9') {
     auto it = std::ranges::find_if(ends, [&](auto &e) { return x == e.x and y == e.y; });
     it->count++;
     if constexpr (p2) {
       return 1u;
     } else {
       return it->count == 1 ? 1u : 0u;
     }
   }

   unsigned s = 0;
   if (data[y + 1][x] == val + 1) { s += score<p2>(x, y + 1, val + 1, ends, data); }
   if (data[y - 1][x] == val + 1) { s += score<p2>(x, y - 1, val + 1, ends, data); }
   if (data[y][x + 1] == val + 1) { s += score<p2>(x + 1, y, val + 1, ends, data); }
   if (data[y][x - 1] == val + 1) { s += score<p2>(x - 1, y, val + 1, ends, data); }

   return s;
}

template <bool p2>
auto score(const POI& head, std::vector<POI> ends, RawData data) {
  return score<p2>(head.x, head.y, '0', ends, data);
}

int main() {

  auto data = RawData{};
  auto input = std::string{};
  bool first = true;
  while (getline(std::cin, input)) {
      if (first) {
          data.push_back(std::string(input.size() + 2, '.'));
          first = false;
      }
      data.push_back('.' + input + '.');
  }
  data.push_back(std::string(data[0].size(), '.'));

  fmt::print("Data \n{}\n", fmt::join(data, "\n"));

  auto [heads, ends] = find_ends(data);

  fmt::print("Heads {}\nEnds{}\n", heads, ends);

   auto s = 0u;
   for (auto h : heads) {
      s += score<false>(h, ends, data);
   }
  fmt::print("Score is: {}\n", s);
  
   s = 0;
   for (auto h : heads) {
      s += score<true>(h, ends, data);
   }
  fmt::print("Score is: {}\n", s);
}

