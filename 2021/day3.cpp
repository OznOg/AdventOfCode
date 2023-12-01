#include <iostream>
#include <vector>
#include <bitset>
#include <string>

int main() {

    std::vector<std::string> input;
    while (std::cin.good()) {
        std::string bits;
        std::cin >> bits;
        if (!std::cin)
            break;
        input.emplace_back(std::move(bits));
    }

    unsigned gamma = 0, epsilon = 0;
    for (auto i = 0u; i < input[0].size(); i++) {

        int c = 0;
        for (auto s : input) {
            c += s[i] == '1' ? 1 : -1;
        }
        gamma <<= 1;
        epsilon <<= 1;
        if (c > 0) {
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }
        

    std::cout << "gamma: " << std::bitset<22>(gamma) << "\n"
                 "epsilon: " << std::bitset<22>(epsilon) << "\n"
                 "result: " << epsilon * gamma << '\n';

}
