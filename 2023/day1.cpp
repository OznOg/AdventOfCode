#include <algorithm>
#include <iostream>
#include <string>


int main() {

    uint64_t sum = 0;
    std::string entry;
    while (std::cin >> entry) {
        entry.erase(std::remove_if(entry.begin(),
                                   entry.end(),
                                   [](const auto &x) { return not std::isdigit(x); }),
                    entry.end());

        auto val = (entry[0] - '0') *10  + (entry.back() - '0');
        sum += val;
    }

    std::cout << "result is: " << sum << '\n';
}

