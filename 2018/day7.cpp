
#include <iostream>
#include <array>
#include <map>
#include <regex>
#include <string>
#include <set>

void part1(std::map<char, std::set<char>> needs) {
    std::cout << "part1: ";
    std::set<char> before;
    do {
        before.clear();
        for (auto &b : needs) {
            if (b.second.size() == 0)
                before.insert(b.first);
        }
        for (auto &c : before) {
            std::cout << c;
            for (auto &b : needs) {
                if (b.second.find(c) != std::end(b.second))
                    b.second.erase(c);
            }
            needs.erase(needs.find(c));
            break;
        }
    } while (before.size() != 0);
    std::cout << std::endl;
}

//#define NB_WORKER 2
//#define SHIFT 0
#define NB_WORKER 5
#define SHIFT 60
bool wip(const std::array<std::pair<char, size_t>, NB_WORKER> &workers) {
    for (auto &w : workers)
        if (w.second != 0)
            return true;
    return false;
}
void part2(std::map<char, std::set<char>> needs) {
    std::array<std::pair<char, size_t>, NB_WORKER> workers;
    ssize_t time = -1;
    do {
        std::cout << "time: " << time;
        for (auto &w : workers) {
            if (w.second != 0) {
                w.second--;
                std::cout << " " << w.first;
            }
        }
        std::cout << std::endl;
        time++;
        for (auto &w : workers) {
            if (w.first != 0 && w.second == 0) {
                auto c = w.first;
                for (auto &b : needs) {
                    if (b.second.find(c) != std::end(b.second))
                        b.second.erase(c);
                }
                needs.erase(needs.find(c));
                std::cout << c;
                w.first = 0; // means thread is free
            }
        }
        std::set<char> before;
        for (auto &b : needs) {
            if (b.second.size() == 0)
                before.insert(b.first);
        }
        for (auto &w : workers) {
            if (w.second != 0)
                before.erase(w.first);
        }
        for (auto &w : workers) {
            if (w.second == 0) {
                if (before.empty())
                    continue;
                auto c = *before.begin();
                w.first = c;
                w.second = SHIFT + c - 'A' + 1;
                before.erase(w.first);
            }
        }
    } while (wip(workers));
    std::cout << "Part2: " << time << std::endl;
}

int main() {

#define CAPTURE(x) (std::string("(") + (x) + std::string(")"))
   
    std::string line_fmt = "^Step " + CAPTURE(".") + " must be finished before step " + CAPTURE(".") + " can begin.$";

    std::string input;

    std::map<char, std::set<char>> needs;
    while (getline(std::cin, input)) {

        std::smatch matches;

        if (std::regex_search(input, matches, std::regex(line_fmt))) {
            auto a = matches[1].str();
            auto b = matches[2].str();
            needs[b[0]].insert(a[0]); 
            needs[a[0]]; 
        } else {
            std::cout << "Cannot parse" << input << std::endl;
        }
    }
    part1(needs);
    part2(needs);
}

