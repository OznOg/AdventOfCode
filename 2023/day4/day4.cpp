
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>


using Card = std::pair<std::set<unsigned>, std::set<unsigned>>;
using Data = std::vector<Card>;

unsigned compute(Data &data, unsigned idx) {
    const auto &[w, o] = data[idx];
    auto count = unsigned{1};
    auto points = unsigned{};

    for (auto &n : o) {
        if (w.contains(n)) {
            points++;
        }
    }

    for (auto i = unsigned{}; i < points; i++) {
       count += compute(data, idx + i + 1);
    }

    return count;
};

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
    

    unsigned total_count = 0;
    for (auto idx = 0u; idx < data.size(); idx++) {
        total_count += compute(data, idx);
    }
    std::cout << "Count is: " << total_count << '\n';
}

