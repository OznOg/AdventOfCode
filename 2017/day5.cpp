
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

size_t run(std::vector<int> instructions) {
    size_t steps = 0;
    auto it = std::begin(instructions);
    while (it < std::end(instructions)) {
        auto offset = *it; 
        (*it)++;
        it += offset;
        steps++;
    }
    return steps;
}

int main() {

    size_t sum = 0;

    std::vector<int> instructions;
    for (std::string linestr; std::getline(std::cin, linestr);) {
        if (linestr.empty())
            break;
        std::istringstream ss(linestr);

        int val;
        ss >> val;
        instructions.push_back(val);
    }

    std::cout << run(instructions) << std::endl;
}

