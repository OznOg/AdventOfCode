#include <list>
#include <iostream>
#include <vector>

void print(size_t step, size_t curr_val, const std::list<size_t> &l) {

    std::cout << step << ":";
    for (auto &e : l)
        if (e == curr_val)
            std::cout << " (" << e << ")";
        else
            std::cout << " " << e;
    
    std::cout << std::endl;
}

#define next(it) do { it = (it == l.end() || std::next(it) == l.end()) ? l.begin() : std::next(it); } while(0)
#define prev(it) do { it = (it == l.begin() ? std::prev(l.end()) : std::prev(it)); } while(0)

//#define PLAYERS 30
//#define MARBLES 5807
#define PLAYERS 459
size_t do_the_job(size_t marbles) {
    // 459 players; last marble is worth 71320 points

    std::list<size_t> l;
    
    const auto nb_player = size_t(PLAYERS);
    std::vector<size_t> players(nb_player);
    l.push_back(0);
    auto it = l.begin();
    size_t curr_player = 0;
    for (auto count = size_t(1); count <= marbles; count++) {
        curr_player++;
        if (curr_player == nb_player + 1)
            curr_player = 1;
        if ((count % 23) != 0 || count == 0) {
            next(it);
            next(it);
            if (it == std::begin(l)) {
                l.push_back(count);
                it = l.end();
                prev(it);
            } else {
                l.insert(it, count);
                prev(it);
            }
        } else {
            prev(it); // 1
            prev(it); // 2
            prev(it); // 3
            prev(it); // 4
            prev(it); // 5
            prev(it); // 6
            prev(it); // 7
            players[curr_player - 1] += count + *it;
            it = l.erase(it);
            if (it == l.end())
                it = l.begin();
        }
        //print(curr_player, *it, l);
    }

    size_t max = 0;
    for (auto &e : players)
        max = std::max(e, max);

    return max;
}

int main() {
#define MARBLES 71320
    std::cout << "Part1: " << do_the_job(MARBLES) << std::endl;
    std::cout << "Part2: " << do_the_job(MARBLES * 100) << std::endl;
}
