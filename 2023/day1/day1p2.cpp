#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>


std::vector<std::pair<unsigned char, std::string>> spelled_digits = {
   { '1',  "one" },
   { '2',  "two" },
   { '3',  "three" },
   { '4',  "four" },
   { '5',  "five" },
   { '6',  "six" },
   { '7',  "seven" },
   { '8',  "eight" },
   { '9',  "nine"}
};


static auto match_spelled_digit(const std::string &s) -> std::optional<std::pair<unsigned char, std::string>> {
    for (auto it = spelled_digits.begin();
            it != spelled_digits.end();
            ++it) {
        if (s.starts_with(it->second))
            return std::make_optional(std::make_pair(it->first, it->second));
    }
    return std::nullopt;
}

int main() {

    uint64_t sum = 0;
    std::string entry;
    while (std::cin >> entry) {
        std::string digits;
        for (int i = 0; i < entry.size(); i++) {
           if (std::isdigit(entry[i])) {
               digits += entry[i];
               continue;
           }

           auto match = match_spelled_digit(entry.substr(i));

           if (!match) continue;

           // THIS part is broken, letters can participate to two digits...
           // i += match->second.size() - 1;
           digits += match->first;
        }

        auto val = (digits[0] - '0') *10  + (digits.back() - '0');
        sum += val;
        std::cout << "entry:\t" << entry << " digit:\t" << digits << " val:\t" << val <<  '\n';
    }

    std::cout << "result is: " << sum << '\n';
}

