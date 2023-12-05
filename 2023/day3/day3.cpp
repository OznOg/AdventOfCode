
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>

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
                for (int k = -1; k < 2; k++)
                    for (int l = -1; l < 2; l++)
                        isPartNum |= isSymbol(data[i + k][j + l]);
                 digitStr = digitStr * 10 + (s[j] - '0');
                 j++;
             }

             if (isPartNum) {
               sumOfParts += digitStr;
             }


        }
        
    }
    std::cout << "Sum of parts: " << sumOfParts << '\n';
    
    std::map<std::pair<unsigned, unsigned>, std::set<unsigned>> parts;
    for (int i = 1; i < data.size() - 1; i++) {
        auto &s = data[i];

        for (int j = 1; j < s.size() - 1; j++) {
             if (not my_isdigit(s[j]))
                 continue;

             bool isPartNum = false;
             unsigned digitStr = 0;
             std::vector<std::pair<unsigned, unsigned>> starPos;
             while (my_isdigit(s[j])) {
                for (int k = -1; k < 2; k++)
                    for (int l = -1; l < 2; l++) {
                        isPartNum |= isSymbol(data[i + k][j + l]);
                        if (data[i + k][j + l] == '*') {
                            starPos.push_back(std::make_pair(i + k, j + l));
                        }
                    }
                 digitStr = digitStr * 10 + (s[j] - '0');
                 j++;
             }

             if (isPartNum) {
               for (auto &p : starPos)
                   parts[p].insert(digitStr);
             }
        }
        
    }


    unsigned sumOfRatios = 0;
    for (auto &[p, v] : parts) {
       if (v.size() == 2) {
           unsigned ratio = 1;
           for (auto &p : v)
             ratio *= p;
           sumOfRatios += ratio;
       }

    }
    std::cout << "Sume of ratios: " << sumOfRatios << '\n';
}

