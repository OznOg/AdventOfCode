


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
#include <ranges>
#include <regex>


auto count_xmas(const std::string &s) {
    auto count = 0u;
    for (auto i = 0u; i < s.size(); i++) {
        if (s.substr(i, std::string::npos).starts_with("XMAS")) {
            count++;
        }
    }
    return count;
}

auto count_xmas(const std::vector<std::string>& input) {
    auto count = 0u;
    for (auto &s : input) {
        count += count_xmas(s);
    }
    return count;
}

auto reverse(const std::vector<std::string>& input) {
    auto reversed = input;
    std::ranges::for_each(reversed, [](auto &s) {
            std::ranges::reverse(s);
            });
    return reversed;
}

// Relies on the fact that input is a square (#lines == #cols)
auto stride(const std::vector<std::string>& input) {
   auto stride = std::vector<std::string>{};
   for (auto j = 0u; j < input.size() - 1; j++) {
     auto up = std::string{};
     auto bott = std::string{};
     
     for (auto i = 0u; i <= j; i++) {
       up.append(1, input[j - i][i]); 
       bott.append(1, input[input.size() - i - 1][input.size() - j + i - 1]); 
     }
     stride.push_back(up);
     stride.push_back(bott);
   }
   
   auto up = std::string{};
   for (auto i = 0u; i < input.size(); i++) {
     up.append(1, input[input.size() - i - 1][i]); 
   }
   stride.push_back(up);
   return stride;
}

auto rotate(const std::vector<std::string>& input) {
  auto rotated = std::vector<std::string>{};
   for (auto i = 0u; i < input.size(); i++) {
     auto line = std::string{};
     for (auto j = 0u; j < input.size(); j++) {
       line.append(1, input[j][i]); 
     }
     rotated.push_back(line);
   }
   return rotated;
}

int main() {

    auto input = std::string{};
    auto data = std::vector<std::string>{};

    while (getline(std::cin, input)) {
        data.push_back(input);
    }

    // data
    auto reversed = reverse(data);
    auto strided = stride(data);
    auto reverse_strided = reverse(strided);
    auto back_strided = stride(reversed);
    auto reverse_back_strided = reverse(back_strided);
    auto rotated = rotate(data);
    auto reverse_rotated = reverse(rotated);

    auto sum = count_xmas(data);
    sum += count_xmas(reversed);
    sum += count_xmas(strided);
    sum += count_xmas(reverse_strided);
    sum += count_xmas(back_strided);
    sum += count_xmas(reverse_back_strided);
    sum += count_xmas(rotated);
    sum += count_xmas(reverse_rotated);

    fmt::print("sum is {}\n", sum);
}

