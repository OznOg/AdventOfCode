
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>


using Data = std::vector<std::pair<std::set<unsigned>, std::set<unsigned>>>;

int main() {
    
    auto data = Data{};
    
    std::string input;
    while (getline(std::cin, input)) {
        auto winning = std::set<unsigned>{};
        auto own = std::set<unsigned>{};
        auto ss = std::stringstream{input};

        auto word = std::string{};

        ss >> word >> word; //to be dropped Card #
        do {
            ss >> word;
            if (word != "|")
                winning.insert(std::stoi(word));
        } while (word != "|");
        
        while  (ss >> word) {
            own.insert(std::stoi(word));
        }

        data.emplace_back(std::make_pair(winning, own));
    }

    unsigned worth = 0;
    for (auto &[w, o] : data) {
        auto points = unsigned{};
        for (auto &n : o) {
           if (w.contains(n)) {
               if (points == 0) {
                   points = 1;
               } else {
                   points <<= 1;
               }
           }
        }
        worth += points;
    }

    std::cout << "Worth is: " << worth << '\n';
}

