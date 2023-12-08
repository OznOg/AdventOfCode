#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>


using NodeList = std::map<std::string, std::pair<std::string, std::string>>;

using Data = std::pair<std::string, NodeList>;

int main() {

    auto data = Data{};

    getline(std::cin, data.first);


    auto input = std::string{};
    getline(std::cin, input); // drop empty line

    while (getline(std::cin, input)) {
       auto label = input.substr(0, 3);;
       auto left = input.substr(7, 3);;
       auto right = input.substr(12, 3);;

       data.second[label] = std::make_pair(left, right);
    }

    auto &[instructions, network] = data;

    auto step = 0u;
    auto next = std::string{"AAA"};
    while (next != "ZZZ") {
        auto &[left, right] = network[next];
        if (instructions[step % instructions.size()] == 'R')
           next = right;
        else
           next = left;
        step++;
    }
    std::cout << "Steps are is: " << step << '\n';
}

