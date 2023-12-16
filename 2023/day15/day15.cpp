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


unsigned char hash(const std::string &s) {
   unsigned h = 0;

   for (auto &c : s) {
         h += c;
         h *= 17;
         h %= 256;
   }
   
   return static_cast<unsigned char>(h);
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
        while (not input.empty()) {
            auto pos = input.find(',');
            data.emplace_back(input.substr(0, pos));
            if (pos != std::string::npos)
                input = input.substr(pos + 1);
            else
                input.clear();
        }
    }

    unsigned sum = 0;

    for (auto &l : data) {
       sum += hash(l);
    }

    std::cout << "Sum is: " << sum << '\n';
}


