
#include <iostream>
#include <map>
#include <string>

size_t do_the_job(std::string state, const std::map<std::string, char> &notes, size_t generations) {
    ssize_t pos = -5;

    for (auto i = 0u; i < generations; i++) {
    //    std::cout << i << ": " << state << std::endl;
       auto next = state;
       for (auto j = 0u; j < state.size() - 5; j++) {
           const auto pattern = state.substr(j, 5);
           if (notes.find(pattern) != std::end(notes))
               next[j + 2] = notes.at(pattern);
           else
               next[j + 2] = '.';
       }
       next = next + (next[next.size() - 5] == '#' ? "." : "");
       if (next[4] != '.') {
           next = "." + next;
           pos -= 1;
       }
       if (next.substr(0, 6) == "......") {
           next = next.substr(1, std::string::npos);
           pos += 1;
       }

       if (state == next) {
           /* At that point the result remains the same pattern but is just
            * shifted right at each iteration, thus just need to count this in
            * pos */
           pos += generations - i - 1;
           break;
       } else
           state = next;
    }

    size_t sum = 0;


    for (auto &c : state) {
        sum += (c == '#' ? pos : 0);
        pos++;
    }
    return sum;
}

int main() {

    std::string input;

    getline(std::cin, input);

    std::string state = "....." + input.substr(15, std::string::npos) + ".....";
    
    getline(std::cin, input);

    std::map<std::string, char> notes;
    while (getline(std::cin, input)) {
        notes[input.substr(0, 5)] = input.back();
    }

    std::cout << "Part1: " << do_the_job(state, notes, 20) << std::endl;
    std::cout << "Part2: " << do_the_job(state, notes, 50000000000ul) << std::endl;
}
