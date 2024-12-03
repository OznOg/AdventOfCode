


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <array>
#include <algorithm>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using Report = std::vector<int>;


auto is_safe(const Report &r) {
    if (r[0] == r.back()) return false;

    auto inc = r[0] < r.back();
    if (inc) {
        auto prev = r[0]; 
        for (auto i = 1; i < r.size(); i++) {
            if (prev >= r[i] or
                    r[i] - prev > 3) {
                return false;
            }
            fmt::print("diff is: {}\n", r[i] - prev);
            prev = r[i];
        }
        return true;
    } else {
        auto prev = r[0]; 
        for (auto i = 1; i < r.size(); i++) {
            if (prev <= r[i] or
                    prev - r[i] > 3) {
                return false;
            }
            fmt::print("diff is: {}\n", prev - r[i]);
            prev = r[i];
        }
        return true;
    }
}

int main() {
    auto data = std::vector<Report>{};
    auto input = std::string{};
    while (getline(std::cin, input)) {
        auto ss = std::stringstream{input};
        auto report = Report{};
        int l;
        while (ss >> l) {
           report.push_back(l);
        }
        data.emplace_back(report);
    }

    fmt::print("data is: {}\n", data);


    auto count = unsigned{0};

    auto idx = 0;
    for (auto &r : data) {
       if (is_safe(r)) {
         count++;
         fmt::print("record {} is safe: {}\n", idx, r);
       }
       idx++;
    }
    fmt::print("safe count is: {}\n", count);
}

