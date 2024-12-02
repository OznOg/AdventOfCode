


#include <fmt/format.h>
#include <algorithm>
#include <format>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<long> left, right;
    long l, r;
    while (std::cin >> l >> r) {
        left.push_back(l);
        right.push_back(r);
    }

    std::sort(begin(left), end(left));
    std::sort(begin(right), end(right));

    if (left.size() != right.size()) {
      throw std::logic_error("list must be the same size");
    }

    unsigned long sum = 0;
    for (auto i = 0u; i < right.size(); i++) {
       sum += std::abs(left[i] - right[i]);
    }

    fmt::print("result is: {}\n", sum);
}

