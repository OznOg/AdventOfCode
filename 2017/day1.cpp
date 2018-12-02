
#include <iostream>
#include <string>
#include <vector>

size_t sumDigits(const std::vector<char> &v) {
    size_t sum = 0;

    for (auto it = std::begin(v); it != std::end(v) - 1; ++it) {
        if (*it == *(it + 1))
            sum += *it;
    }
    return sum;
}

int main() {
    std::string inputstr;
    std::cin >> inputstr;

    std::vector<char> input;

    for (const auto &c : inputstr) {
        input.push_back(c - '0');
    }

    /* copy the first element to the end so that i don't bother with going backward */
    input.push_back(input[0]);

    std::cout << sumDigits(input) << std::endl;
}

