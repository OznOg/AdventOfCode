
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>

size_t compute(std::vector<size_t> inputs) {
    size_t count = 0;
    std::set<std::vector<size_t>> history;

    while (history.find(inputs) == history.end()) {
        history.insert(inputs);

        auto it = std::max_element(inputs.begin(), inputs.end());

        auto val = *it;
        *it = 0;
        for (;val != 0; val--) {
            ++it;
            if (it == inputs.end()) {
                it = inputs.begin();
            }
            (*it)++;
        }
        count++;
    }
    return count;
}

int main(int argc, char **argv) {
    std::vector<size_t> inputs;
    for (int i = 1; i < argc; ++i) {
        inputs.push_back(std::atoi(argv[i]));
    } 

#if 0
    if (inputs.size() != 16) {
        std::cerr << "missing values (expected 16, got" << inputs.size() << ")\n";
        return 2;
    }
#endif

    std::cout << compute(inputs) << std::endl;
}
