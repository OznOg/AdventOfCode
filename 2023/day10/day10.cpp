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
            data.emplace_back(std::string(input.size() + 2, '.'));
            first = false;
        }
       data.emplace_back("." + input + ".");
    }
    data.emplace_back(std::string(data.back().size(), '.'));

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

   auto path = std::vector<std::pair<unsigned, unsigned>>{};
   path.push_back(origin);
   auto prev = origin;
   auto curr = find_start_first_pipe(data, {x, y});
   path.push_back(curr);

   unsigned count = 1;
   while (curr != std::make_pair(x, y)) {
       //std::cout << "curr is (x:" << curr.first - 1 << ", y:" << curr.second  - 1 << ")\n";
       auto old_curr = curr;
       curr = next(data, prev, curr);
       prev = old_curr;
       path.push_back(curr);
       count++;
   }

   std::cout << "Size of loop is: " << count << " farther place is: " << static_cast<unsigned>(ceil(count/2.)) << '\n';

   Data data_clean;

   for (auto j = unsigned{0}; j < data.size(); j++) {
       auto l = data[j];
       for (auto i = unsigned{0}; i < l.size(); i++) {
           auto it = find(path.begin(), path.end(), std::make_pair(i, j));
           if (it == path.end()) {
               // not part of path, cleanu the value
               l[i] = '.';
           }
           if (l[i] == 'S') { // FIX S
               std::set<unsigned char> s;
               s.insert('J');
               s.insert('L');
               s.insert('F');
               s.insert('7');
               s.insert('|');
               s.insert('-');
               if (l[i + 1] == 'J' || l[i + 1] == '-' || l[i + 1] == '7') {
                  s.erase('|');
                  s.erase('7');
                  s.erase('J');
               }
               if (l[i - 1] == 'F' || l[i - 1] == 'L' || l[i - 1] == '-') {
                  s.erase('|');
                  s.erase('F');
                  s.erase('L');
               }
               if (data[j + 1][i] == 'J' || data[j + 1][i] == 'L' || data[j + 1][i] == '|') {
                  s.erase('-');
                  s.erase('J');
                  s.erase('L');
               }
               if (data[j - 1][i] == '7' || data[j - 1][i] == 'F' || data[j - 1][i] == '|') {
                  s.erase('-');
                  s.erase('7');
                  s.erase('F');
               }
               l[i] = *s.begin();
               std::cout << "Fixed S with:" << l[i] << '\n';
           }
       }
       data_clean.push_back(l);
   }

   bool in = false;;
   for (auto j = unsigned{0}; j < data_clean.size(); j++) {
       auto &l = data_clean[j];
       for (auto i = unsigned{0}; i < l.size(); i++) {
          auto &c = l[i];
          switch (c) {
           case '|':
             in = !in;
             break;

           case 'L':
             for (i++; i < l.size() && l[i] == '-'; i++) {
             }
             if (l[i] == '7') in = !in;
             break;
           case 'F':
             for (i++; i < l.size() && l[i] == '-'; i++) {
             }
             if (l[i] == 'J') in = !in;
             break;
           case 'J':
           case '7':
           case 'S':
           case 'O':
           case 'I':
           break;
           case '-':
           break;
           case '.':
              l[i] = in ? 'I' : 'O';
           break;
           default:
             throw "WTF";
          }
      }

   }

   
   count = 0;
   for (const auto &l : data_clean) {
       std::cout << l << '\n';
      for (const auto &c : l) {
         if (c == 'I') count++;
      }
   }

   std::cout << "Enclosed tiles count is: " << count << '\n';

}


