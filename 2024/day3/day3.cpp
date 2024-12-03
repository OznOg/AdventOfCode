


#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>


int main() {

    auto all_inputs = std::vector<std::string>{};
    auto input = std::string{};

    while (getline(std::cin, input)) {
       all_inputs.emplace_back(std::move(input));
    }
    std::regex r(R"(mul\(([1-9]\d?\d?),([1-9]\d?\d?)\))");

    auto sum = 0ull;
    for (auto input : all_inputs) {
      for (std::smatch sm; regex_search(input, sm, r);)
      {
        fmt::print("found {} ;  operands are {}, {}\n", sm.str(), sm[1].str(), sm[2].str());

        sum += stol(sm[1].str()) * stol(sm[2].str());
        input = sm.suffix();
      }
    }
    fmt::print("sum is {}\n", sum);
}

