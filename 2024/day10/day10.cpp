


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


auto score(int x, int y, int val, const std::vector<POI>& ends, RawData& data) {
   if (val == '9') {
     data[y][x] = '.'; // invalidate end
     return 1u;
   }

   unsigned s = 0;
   if (data[y + 1][x] == val + 1) { s += score(x, y + 1, val + 1, ends, data); }
   if (data[y - 1][x] == val + 1) { s += score(x, y - 1, val + 1, ends, data); }
   if (data[y][x + 1] == val + 1) { s += score(x + 1, y, val + 1, ends, data); }
   if (data[y][x - 1] == val + 1) { s += score(x - 1, y, val + 1, ends, data); }

   return s;
}

auto score(const POI& head, const std::vector<POI>& ends, RawData data) {
  return score(head.x, head.y, '0', ends, data);
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
      s += score(h, ends, data);
   }
  fmt::print("Score is: {}\n", s);
  
}

