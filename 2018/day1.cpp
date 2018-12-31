
#include <iostream>

int main() {
    int64_t sum = 0;
    int64_t val;
    while ((std::cin >> val)) {
        sum += val;
    }

    std::cout << sum << std::endl;
}

