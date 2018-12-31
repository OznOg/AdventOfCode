#include <list>
#include <iostream>
#include <sstream>
#include <vector>

void print(size_t step, size_t currA, size_t currB, const std::list<size_t> &l) {

    std::cout << step << ":";
    for (auto &e : l)
        if (e == currA)
            std::cout << " (" << e << ")";
        else if (e == currB)
            std::cout << " [" << e << "]";
        else
            std::cout << " " << e;
    std::cout << std::endl;
}

//#define next(it) do { it = (it == board.end() || std::next(it) == board.end()) ? board.begin() : std::next(it); } while(0)
#define next(it) do { it = (it == board.size() || it + 1 == board.size()) ? 0 : it + 1; } while(0)
#define prev(it) do { it = (it == board.begin() ? std::prev(board.end()) : std::prev(it)); } while(0)

auto do_the_job(size_t recipies) {
    std::string board = "37";
    size_t itA = 0;
    size_t itB = itA + 1;

    for (auto i = 0u; board.size() < recipies + 10; i++) {
         char a = board[itA] - '0';
         char b = board[itB] - '0';
         auto res = a + b;
         std::string temp;
         temp.insert(0, 1, (res % 10) + '0');
         res /= 10;
         if (res != 0)
              temp.insert(0, 1, (res % 10) + '0');
         board += temp;
         //std::cout << board << std::endl;
         for (auto j = 0; j < a + 1; j++)
             next(itA);
         for (auto j = 0; j < b + 1; j++)
             next(itB);
    }
    return board.substr(recipies, 10);
}

auto do_the_job2(size_t value) {
    std::string board = "37";
    size_t itA = 0;
    size_t itB = itA + 1;


    std::stringstream ss;
    ss << value;
    auto pattern = ss.str();

    auto count = 0;
    auto idx = board.find(pattern);

    while (idx == std::string::npos) {
        for (auto i = 0u; i < 400; i++) {
            char a = board[itA] - '0';
            char b = board[itB] - '0';
            auto res = a + b;
            std::string temp;
            temp.insert(0, 1, (res % 10) + '0');
            res /= 10;
            if (res != 0)
                temp.insert(0, 1, (res % 10) + '0');
            board += temp;
            //std::cout << board << std::endl;
            for (auto j = 0; j < a + 1; j++)
                next(itA);
            for (auto j = 0; j < b + 1; j++)
                next(itB);
        }

        idx = board.find(pattern, count - 10);
        count += 400;
    }
    return board.find(pattern);
}

int main() {
#define RECIPIES 824501
    std::cout << "Part1: " << do_the_job(RECIPIES) << std::endl;
    std::cout << "Part2: " << do_the_job2(RECIPIES) << std::endl;
}
