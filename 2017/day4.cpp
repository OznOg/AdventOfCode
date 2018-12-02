
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

int main() {

    size_t sum = 0;

    for (std::string linestr; std::getline(std::cin, linestr);) {
        if (linestr.empty())
            break;
        std::set<std::string> set;
        std::istringstream ss(linestr);

        // parse each line loking for words
        // we put them in a set, if the word count does not match the set size,
        // this means that the same word was given twice => ignore the line
        size_t word_count = 0;
        while (ss && word_count == set.size()) {
            std::string word;
            ss >> word;
            set.insert(word);
            word_count++;
        }
        if (word_count == set.size())
            sum++;
    }

    std::cout << sum << std::endl;
}

