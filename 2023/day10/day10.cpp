#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <set>
#include <optional>


using Line = std::string;
using Data = std::vector<Line>;


std::pair<unsigned, unsigned> next(const Data &data, const std::pair<unsigned, unsigned> &prev, const std::pair<unsigned, unsigned> &curr) {
   

    switch (data[curr.second][curr.first]) {
        case '|': // is a vertical pipe connecting north and south.
            if (prev.second == curr.second + 1)
                return std::make_pair(curr.first, curr.second - 1);
            else
                return std::make_pair(curr.first, curr.second + 1);
        case '-': // is a horizontal pipe connecting east and west.
            if (prev.first == curr.first + 1)
                return std::make_pair(curr.first - 1, curr.second);
            else
                return std::make_pair(curr.first + 1, curr.second);
        case 'L': // is a 90-degree bend connecting north and east.
            if (prev.second == curr.second - 1)
                return std::make_pair(curr.first + 1, curr.second);
            else
                return std::make_pair(curr.first, curr.second - 1);
        case 'J': // is a 90-degree bend connecting north and west.
            if (prev.second == curr.second - 1)
                return std::make_pair(curr.first - 1, curr.second);
            else
                return std::make_pair(curr.first, curr.second - 1);
        case '7': // is a 90-degree bend connecting south and west.
            if (prev.second == curr.second + 1)
                return std::make_pair(curr.first - 1, curr.second);
            else
                return std::make_pair(curr.first, curr.second + 1);
        case 'F': // is a 90-degree bend connecting south and east.
            if (prev.second == curr.second + 1)
                return std::make_pair(curr.first + 1, curr.second);
            else
                return std::make_pair(curr.first, curr.second + 1);
        case 'S': // is the starting position of the animal; there is a pipe on this
        case '.': // is ground; there is no pipe in this tile.
            break;
    }
    throw "WTF";
}

auto find_start_first_pipe(const Data& data, const std::pair<unsigned, unsigned> &startpos) {

    if (std::string("-J7").find(data[startpos.second][startpos.first + 1]) != std::string::npos)
        return std::make_pair(startpos.first + 1, startpos.second);
    if (std::string("-LF").find(data[startpos.second][startpos.first - 1]) != std::string::npos)
        return std::make_pair(startpos.first - 1, startpos.second);
    if (std::string("|LJ").find(data[startpos.second + 1][startpos.first]) != std::string::npos)
        return std::make_pair(startpos.first, startpos.second + 1);
    if (std::string("|F7").find(data[startpos.second - 1][startpos.first]) != std::string::npos)
        return std::make_pair(startpos.first, startpos.second - 1);
    throw "WTf";
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    bool first = true;
    while (getline(std::cin, input)) {
        if (first) {
            data.emplace_back(std::string('.', input.size() + 2));
            first = false;
        }
       data.emplace_back("." + input + ".");
    }
    data.emplace_back(std::string('.', data.back().size()));

   std::cout << data.size() << '\n';

   auto origin = std::pair<unsigned, unsigned>{};
   auto &[x, y] = origin;
   // find start position
   for (auto &l : data) {
      if (l.find('S') != std::string::npos) {
        x = l.find('S');
        y = &l - &data[0];
        break;
      }
   }

   auto prev = origin;
   auto curr = find_start_first_pipe(data, {x, y});

   unsigned count = 1;
   while (curr != std::make_pair(x, y)) {
       std::cout << "curr is (x:" << curr.first - 1 << ", y:" << curr.second  - 1 << ")\n";
       auto old_curr = curr;
       curr = next(data, prev, curr);
       prev = old_curr;
       count++;
   }

   std::cout << "Size of loop is: " << count << " farther place is: " << static_cast<unsigned>(ceil(count/2.)) << '\n';
}


