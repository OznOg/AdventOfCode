
#include <set>
#include <vector>
#include <iostream>
#include <tuple>
#include <array>


std::pair<bool, bool> has_2_or_3(const std::string &s) {
    std::array<size_t, 26> counts = {};
    for (auto &c : s)
        counts[c - 'a']++;

    bool has2 = false, has3 = false;
    for (auto e : counts) {
        has2 |= (e == 2);
        has3 |= (e == 3);
    }
    return std::make_pair(has2, has3);
}

int main() {

    std::string input;
    std::vector<std::string> inputs;
    while ((std::cin >> input)) {
        inputs.push_back(input);
    }

    size_t two_count = 0, three_count = 0;
    for (auto &v : inputs) {
        bool has2 = false, has3 = false;
        std::tie(has2, has3) = has_2_or_3(v);
        if (has2)
            two_count++;
        if (has3)
            three_count++;
    }
    std::cout << "checksum is " << two_count << " * " << three_count << " = " << two_count * three_count << std::endl;
}

