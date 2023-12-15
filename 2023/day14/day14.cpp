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


Data transpose(const Data &data) {
   auto transposed = Data(data.front().size());
   for (auto &l : transposed) {
      l = std::string(data.size(), ' ');
   }

   for (auto i = 0u; i < data.front().size(); i++) {
       for (auto j = 0u; j < data.size(); j++) {
          transposed[i][j] = data[j][i]; 
       }
   }
   return transposed; 
}

Data tilt(const Data &data) {
    auto tilted = Data(data.size());

    for (auto j = 0u; j < data.size(); j++) {
        for (auto i = 0u; i < data[j].size(); i++) {
           auto &l = data[j];
           if (l[i] == 'O')
              tilted[j].append(1, 'O');
           else if (l[i] == '#') {
              for (auto k = tilted[j].size(); k < i; k++) {
                  tilted[j].append(1, '.');
              }
              tilted[j].append(1, '#');
           }
              
        }
        tilted[j].append(data[j].size() - tilted[j].size(), '.');
    }
    return tilted;
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
        data.emplace_back(input);
    }


    auto transposed = transpose(data);
    auto tilted = tilt(transposed);

    for (auto &l : tilted)
        std::cout << l << '\n';

    auto sum = 0;
    for (auto &l : tilted) {
       for (auto i = 0u; i < l.size(); i++) {
           if (l[i] == 'O') {
              sum += l.size() - i;
           }
       }
    }

    std::cout << "Sum is: " << sum << '\n';
}


