#include <iostream>
#include <string>
#include <vector>
#include <optional>


int main() {
    std::vector<uint64_t> depths;

    while (std::cin.good()) {
        depths.resize(depths.size()+1);
        
        std::cin >> depths.back();
    }

    auto stop = depths.end() - 3;

    std::optional<int64_t> prev;

    size_t nb_increaded = 0;

    std::vector<uint64_t> s_depths;
    s_depths.reserve(depths.size());

    for (auto it = depths.begin(); it != stop; ++it) {
        s_depths.push_back(*it + *(it + 1) + *(it + 2));
    }
    
    for (auto depth : s_depths) {
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
