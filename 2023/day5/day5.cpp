
#include <array>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>


struct Range {
   unsigned dstart, sstart, length;
};

struct Map {
    std::string src;
    std::string dest;
    std::vector<Range> ranges;
};

using Data = std::pair<std::vector<unsigned>, std::vector<Map>>;

int main() {

    auto data = Data{};

    auto &[seeds, maps] = data;

    std::string input;
    {
        getline(std::cin, input);

        auto ss = std::stringstream{input};
        ss >> input; // drop seed

        auto val = unsigned{};
        while (ss >> val)
            seeds.push_back(val);

        // empty line
        getline(std::cin, input);
    }

    maps.reserve(1000);
    maps.resize(1);
    
    auto *map = &maps.back();
    while (getline(std::cin, input)) {
      
       auto pos = input.find('-'); 
       map->src = input.substr(0, pos);
       pos += std::string_view("-to-").size();
       map->dest = input.substr(pos, input.find(' ') - pos);

       while (getline(std::cin, input) && not input.empty()) {
           Range range;
           auto ss = std::stringstream{input};
           ss >> range.dstart >> range.sstart >> range.length;
           map->ranges.emplace_back(std::move(range));
       }

       if (std::cin) {
           maps.resize(maps.size() + 1);
           map = &maps.back();
       }
    }

   auto to_next = [] (unsigned val, const Map &map) {
      for (auto& r : map.ranges) {
        if (val >= r.sstart && val < r.sstart + r.length) {
            return r.dstart + (val - r.sstart);
        }
      }
      return val;
   };

   auto location = std::numeric_limits<unsigned>::max();
   for (const auto &seed : seeds) {
       auto val = seed;
       for (const auto &map : maps) {
          val = to_next(val, map);
       }
       location = std::min(location, val);
   }
   std::cout << "Location is: " << location << '\n';

   location = std::numeric_limits<unsigned>::max();
   for (auto i = 0u; i < seeds.size(); i+=2) {
       for (auto seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; seed++) {
           auto val = seed;
           for (const auto &map : maps) {
               val = to_next(val, map);
           }
           location = std::min(location, val);
       }
   }
   std::cout << "Location #2 is: " << location << '\n';
}

