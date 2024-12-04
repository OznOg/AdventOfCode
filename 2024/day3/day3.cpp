


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

    auto input = std::string{};
    auto all_inputs = std::string{};

    while (getline(std::cin, input)) {
        all_inputs += input;
    }
    std::regex r(R"(mul\(([1-9]\d?\d?),([1-9]\d?\d?)\))");

    {
        // p1
        auto sum = 0ull;
        input  = all_inputs;
        for (std::smatch sm; regex_search(input, sm, r);)
        {
            fmt::print("found {} ;  operands are {}, {}\n", sm.str(), sm[1].str(), sm[2].str());

            sum += stol(sm[1].str()) * stol(sm[2].str());
            input = sm.suffix();
        }
        fmt::print("sum is {}\n", sum);
    }
    {
        // p2
        static const std::string d0 = "do()";
        static const std::string d0nt = "don't()";
        auto sum = 0ull;
        auto search = d0nt; 
        bool active = true;
        size_t pos = 0;
        input  = all_inputs + d0nt;
        std::vector<std::string> good_inputs;
        while ((pos = input.find(active ? d0nt : d0)) != std::string::npos) {
            if (active)
                good_inputs.push_back(input.substr(0, pos)); 
            input = input.substr(pos, std::string::npos);
            active = not active;
        }
        for (auto input : good_inputs) {
            fmt::print("working on {}\n", input);
            for (std::smatch sm; regex_search(input, sm, r);)
            {
                fmt::print("found {} ;  operands are {}, {}\n", sm.str(), sm[1].str(), sm[2].str());

                sum += stol(sm[1].str()) * stol(sm[2].str());
                input = sm.suffix();
            }
        }
        fmt::print("sum is {}\n", sum);
    }

}

