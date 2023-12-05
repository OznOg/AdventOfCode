
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

bool my_isdigit(char ch)
{
    return std::isdigit(static_cast<unsigned char>(ch));
}

bool isSymbol(char c) {
    return c != '.' and not my_isdigit(c);
}

int main() {
    std::vector<std::string> data;

    // read and add dots on first/last lines and first/lact columns to ease computations
    std::string input;
    bool first = true;
    while (getline(std::cin, input)) {
        if (first) {
          first = false;
          data.push_back(std::string(input.size() + 2, '.'));
        }
        data.push_back(std::string(".") + input + ".");
    }
    data.push_back(std::string(data.back().size() + 2, '.'));

    
    for (auto & i : data)
        std::cout << i << '\n';

    unsigned sumOfParts = 0;
    for (int i = 1; i < data.size() - 1; i++) {
        auto &s = data[i];

        for (int j = 1; j < s.size() - 1; j++) {
             if (not my_isdigit(s[j]))
                 continue;

             bool isPartNum = false;
             unsigned digitStr = 0;
             while (my_isdigit(s[j])) {
                 isPartNum |=
                     isSymbol(s[j - 1])
                     or isSymbol(s[j + 1])
                     or isSymbol(data[i - 1][j]) or isSymbol(data[i - 1][j - 1]) or isSymbol(data[i - 1][j + 1])
                     or isSymbol(data[i + 1][j]) or isSymbol(data[i + 1][j - 1]) or isSymbol(data[i + 1][j + 1]);
                 digitStr = digitStr * 10 + (s[j] - '0');
                 j++;
             }

             if (isPartNum) {
               std::cout << digitStr << '\n';
               sumOfParts += digitStr;
             }


        }
        
    }
    std::cout << "Sum of parts: " << sumOfParts << '\n';
}

