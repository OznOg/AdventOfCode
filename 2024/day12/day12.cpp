

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


struct Garden {
    unsigned x, y;
    friend auto format_as(const Garden &g) {
       return std::tie(g.x, g.y);
    }
};

struct Region {
    unsigned char plant;
    std::vector<Garden> gardens;
    
    friend auto format_as(const Region &r) {
       return fmt::format("[{}, {}", r.plant, r.gardens);
    }
};

using Map = std::vector<std::string>;


auto find_touching(g, std::vector<Regions> regions) {
    Region* maybe_region = nullptr;

}

auto  make_regions(const Map& map) {
   auto regions = std::vector<Regions>{};

   for (auto &raw : map) {
       for (auto &col : raw) {
         auto maybe_region = find_touching(regions);
       }
   }
}


int main() {

  auto map = Map{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      map.push_back(input);
  }

  fmt::print("Map is:\n{}\n", fmt::join(map, "\n"));
  
  auto regions = make_regions(map);

}

