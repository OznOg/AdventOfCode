
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using Set = std::vector<std::pair<unsigned, std::string>>;
using Game = std::vector<Set>;
using Data = std::map<unsigned, Game>;

Set parse_set(std::string input) {
    auto set = Set{};
    do { 
        auto pos = input.find(',');
        auto str = input.substr(0, pos);

        std::stringstream ss(str);

        unsigned count = 0;
        std::string color;
        ss >> count >> color;

        set.emplace_back(count, color);

        if (pos != std::string::npos)
            input = input.substr(pos + 1);
        else
            input.clear();
    } while (not input.empty());
    return set;
};

void handle_input(std::vector<Set> &set, std::string input) {
    auto data = Data{};

    do { 
        auto pos = input.find(';');
        auto str = input.substr(0, pos);

        set.push_back(parse_set(str));

        if (pos != std::string::npos)
            input = input.substr(pos + 1);
        else
            input.clear();
    } while (not input.empty());
}

std::map<std::string, unsigned> ref = {std::make_pair<std::string, unsigned>("red", 12), { "green", 13}, { "blue", 14 } };
int main() {
    std::string input;


    auto data = Data{};

    auto id = 1;
    while (getline(std::cin, input)) {

        input = input.substr(input.find(':') + 1);
        
        handle_input(data[id], input);
        
        id++;
    }

    //for (const auto &[i, vg] : data) {
    //    std::cout << "{";
    //    for (const auto &g : vg) {
    //        std::cout << "  {";

    //        for (auto &[n, c] : g) {
    //            std::cout << ' ' << n << ' ' << c;
    //        }
    //        std::cout << " }\n";
    //    }
    //    std::cout << "}\n";
    //}

    auto isSetPossible = [&] (const Set &set) {
        for (auto &[n, c] : set) {
            if (n > ref[c])
                return false;
        }
        return true;
    };

    auto isGamePossible = [&] (const Game &game) {
        for (const auto &s : game) {
           if (not isSetPossible(s))
             return false;
        }
        return true;
    };

    unsigned sumOfIds = 0;
    for (const auto &[i, g] : data) {
       if (isGamePossible(g)) {
          sumOfIds += i;       
       }
    }

    std::cout << "Sum of ids is: " << sumOfIds << '\n';

    auto powerOfGame = [] (const Game &game) {
        unsigned max_r = 0;
        unsigned max_g = 0;
        unsigned max_b = 0;
        for (const auto &s : game) {
            for (auto &[n, c] : s) {
               if (c == "red")
                max_r = std::max(n, max_r);
               if (c == "green")
                max_g = std::max(n, max_g);
               if (c == "blue")
                max_b = std::max(n, max_b);
            }
        }
        return max_r * max_g * max_b;
    };

    unsigned sumOfPowers = 0;
    for (const auto &[i, g] : data) {
        sumOfPowers += powerOfGame(g);
    }
    std::cout << "Sum of powers is: " << sumOfPowers << '\n';
}

