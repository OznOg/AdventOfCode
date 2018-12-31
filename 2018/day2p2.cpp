
#include <set>
#include <vector>
#include <iostream>
#include <tuple>
#include <array>


bool match(const std::string &s1, const std::string &s2) {

    size_t idx = 0;
    size_t matched = 0;
    for (auto &c : s1)
        if (c == s2[idx++])
            matched++;

    return s1.size() == matched + 1;
}


std::pair<std::string, std::string> find_match(const std::vector<std::string> &inputs) {
    for (auto i = 0u; i < inputs.size() - 1; i++) {
        for (auto j = i + 1; j < inputs.size(); j++) {
            if (match(inputs[i], inputs[j]))
                return std::make_pair(inputs[i], inputs[j]);
        }
    }
    throw "bug, not found";
}

std::string similitude(const std::string &s1, const std::string &s2) {

    size_t idx = 0;
    std::string simili;
    for (auto &c : s1)
        if (c == s2[idx++])
            simili.append(1, c);

    return simili;
}

int main() {

    std::string input;
    std::vector<std::string> inputs;
    while ((std::cin >> input)) {
        inputs.push_back(input);
    }

    std::string s1, s2;
    std::tie(s1, s2) = find_match(inputs);

    std::cout << "found " << s1 << " and " << s2 << std::endl;

    std::cout << "result is: " << similitude(s1, s2) << std::endl;
}

