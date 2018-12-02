
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

std::list<size_t> hash(std::list<size_t> elements, const std::vector<size_t> lengths) {
    size_t skip = 0;
    auto copy = std::list<size_t>(elements.begin(), elements.begin() + lengths[0]);
    for (size_t l = 0; l < lengths[0]; l++) {
    }
}


int main() {
    std::vector<size_t> lengths;

    while (std::cin.good()) {
        std::string lengthstr;
        getline(std::cin, lengthstr, ',');
        std::istringstream ss(lengthstr);
        size_t length;
        ss >> length;

        lengths.push_back(length);
    }

    std::list<size_t> elements;
    for (size_t i = 0; i < 255; ++i) {
        elements.push_back(i);
    }
}
