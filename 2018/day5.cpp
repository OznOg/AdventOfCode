
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

constexpr char shift = 'a' - 'A';
std::string react(std::string &&input) {
    bool did_something = false;
    do {
       did_something = false;
       for (auto idx = 0u; idx < input.size() - 1;) {
           if (input[idx] == input[idx + 1] + shift
                           || input[idx + 1] == input[idx] + shift) {
               did_something = true;
               input = input.substr(0, idx) + ((idx != input.size() - 2) ? input.substr(idx + 2, std::string::npos) : std::string());
           } else
               idx++; // don't move forward when erasing elements
       }
    } while (did_something && input.size() > 1);

    return input;
}

int main() {

    std::string input;
    std::cin >> input;

    //part1

    std::cout << "result part1=" << react(std::string(input)).size() << std::endl;

    auto min = std::numeric_limits<size_t>::max();
    for (auto c = 'A'; c <= 'Z'; c++) {
        std::string cleaned = input;
        cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), c), cleaned.end());
        cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), c + shift), cleaned.end());
        auto result = react(std::move(cleaned));
        min = std::min(min, result.size());
    }
    std::cout << "part2, overal smallest =" << min << std::endl;
}
