#include <iostream>
#include <string>
#include <optional>


int main() {
    std::optional<int64_t> prev;

    size_t nb_increaded = 0;

    while (std::cin.good()) {
        int64_t depth;
        std::cin >> depth;
        
        std::cout << depth << ' ';
        if (!prev)
            std::cout << "(N/A - no previous measurement)\n";
        else {
            std::cout << (depth > *prev ? "(increased)" : "(decreased)" ) << '\n';
            nb_increaded += depth > *prev;
        }
        prev = depth;
    }

    std::cout << "result is " << nb_increaded << '\n';
}
