#include <iostream>
#include <vector>
#include <string>

int main() {

    std::vector<std::pair<char, size_t>> input;
    while (std::cin.good()) {
        int64_t value;
        std::string cmd;
        std::cin >> cmd >> value;
        if (std::cin)
            input.emplace_back(std::make_pair(cmd[0], value));
    }

    size_t hpos = 0, depth = 0;
    for (auto i : input) {
        switch(i.first) {
        case 'u':
            depth -= i.second;
            break;
        case 'd':
            depth += i.second;
            break;
        case 'f':
            hpos += i.second;
            break;
        default:
            throw "bad";
        }
    }
    std::cout << hpos * depth << '\n';
}
