

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
    int x, y;
    friend auto format_as(const Garden &g) {
       return std::tie(g.x, g.y);
    }
};

struct Region {
    unsigned char plant;
    size_t fence_length = 0;
    std::vector<Garden> gardens;
    
    friend auto format_as(const Region &r) {
       return fmt::format("[p = {}, l = {}, area = {}, {}]", std::string(1, r.plant), r.fence_length, r.gardens.size(), r.gardens);
    }
};

using Map = std::vector<std::string>;


void crawl_region(int x, int y, Region& region, Map &map) {
   if (map[y][x] != region.plant) {
     return;
   }

   auto g = Garden{};
   g.x = x;
   g.y = y;
   region.gardens.push_back(g);
   map[y][x] -= '@';

   if (map[y + 1][x] != region.plant && map[y + 1][x] != region.plant - '@') region.fence_length++;
   if (map[y - 1][x] != region.plant && map[y - 1][x] != region.plant - '@') region.fence_length++;
   if (map[y][x + 1] != region.plant && map[y][x + 1] != region.plant - '@') region.fence_length++;
   if (map[y][x - 1] != region.plant && map[y][x - 1] != region.plant - '@') region.fence_length++;

   crawl_region(x + 1, y, region, map);
   crawl_region(x - 1, y, region, map);
   crawl_region(x, y + 1, region, map);
   crawl_region(x, y - 1, region, map);
}

auto  make_regions(const Map& _map) {
   auto regions = std::vector<Region>{};
   auto map = _map;

   for (auto y = 1; y < map.size() - 1; y++) {
       for (auto x = 1; x < map.front().size() - 1; x++) {
          if (map[y][x] <= '@') {
             continue;
          }
         auto region = Region{};
         region.plant = map[y][x];
         crawl_region(x, y, region, map);
         regions.push_back(region);
       }
   }
   return regions;
}

int main() {

  auto map = Map{};
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
  
  auto regions = make_regions(map);

  fmt::print("Regions are:\n{}\n", fmt::join(regions, "\n   "));

  unsigned long long sum = 0;
  for (auto r : regions) {
     sum += r.gardens.size() * r.fence_length;
  }

  fmt::print("Sum is: {}\n", sum);
  
}

