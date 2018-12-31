
#include <set>
#include <vector>
#include <iostream>

int main() {

    int64_t val;
    std::vector<int64_t> inputs;
    while ((std::cin >> val)) {
        inputs.push_back(val);
    }

    int64_t sum = 0;
    std::set<int64_t> history;
    history.insert(sum);
    while (true) {
        for (auto &v : inputs) {
            sum += v;
            if (history.find(sum) != std::end(history)) {
                std::cout << sum << std::endl;
                return 0;
            }
            history.insert(sum);
        }
    }
    std::cout << "size" << history.size() << std::endl;
}

