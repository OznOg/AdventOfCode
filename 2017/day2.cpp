
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {

    size_t sum = 0;

    for (std::string linestr; std::getline(std::cin, linestr);) {
        if (linestr.empty())
            break;
        std::vector<size_t> line;
        std::istringstream ss(linestr);

        while (ss) {
            int val;
            ss >> val;
            line.push_back(val);
        }
        auto max = std::max_element(line.begin(), line.end());
        auto min = std::min_element(line.begin(), line.end());

        //std::cout << *max << " " << *min << std::endl;
        sum += *max - *min;
    }

    std::cout << sum << std::endl;
}

