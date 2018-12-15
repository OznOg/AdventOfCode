

#include <array>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using Point = std::pair<unsigned short, unsigned short>;

static Point mkPoint(unsigned short x, unsigned short y) {
    return std::make_pair(x, y);
}

int abs(int t) {
    if (t > 0)
        return t;
    else
        return -t;
}

unsigned short dist(const Point &a, const Point &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// In a general situation, we would need to find the zone in which it is 
// usefull to search as coordinates may be anywhere in the plan.
// That said here the data set is known and the max values do not go above 400
// so I hardcode it here
#define SIZE 400
static size_t part1(const std::vector<Point> &inputs) {
    std::array<std::pair<unsigned short, unsigned short>, SIZE * SIZE> board = {};

    // initialize board
    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i++) {
            board[i + j * SIZE].first  = 65535;
            board[i + j * SIZE].second  = 65535;
        }
    }

    // for each point, find the point which is closest and what is the distance
    // to it
    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i++) {
            size_t idx = 0;
            auto l = mkPoint(i, j);
            for (auto &p : inputs) {
                if (board[i + j * SIZE].first > dist(p, l)) {
                    board[i + j * SIZE].first = dist(p, l);
                    board[i + j * SIZE].second = idx;
                } else if (board[i + j * SIZE].first == dist(p, l)
                           && board[i + j * SIZE].second != idx) {
                    board[i + j * SIZE].second = 65535;
                }
                idx++;
            }
        }
    }

    // As points on the surronding to the board are delimiting the infinite
    // zones, we discard every point that is on edges
    std::set<unsigned short> bad_idx; 
    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i += SIZE - 1) {
             bad_idx.insert(board[i + j * SIZE].second);
        }
    }
    for (auto j = 0u; j < SIZE; j += SIZE - 1) {
        for (auto i = 0u; i < SIZE; i++) {
             bad_idx.insert(board[i + j * SIZE].second);
        }
    }

    // spzcial case for equidistant point that are discarded directly
    bad_idx.insert(65535);
    std::vector<size_t> sizes(inputs.size());
    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i++) {
            const auto &idx = board[i + j * SIZE].second;
            if (bad_idx.find(idx) != std::end(bad_idx)) {
                continue;
            }
            sizes[idx]++;
        }
    }

    size_t max = 0u;
    for (auto &s : sizes)
        max = std::max(s, max);

    return max;
}

#define MAX_DIST 10000
static size_t part2(const std::vector<Point> &inputs) {
    std::array<size_t, SIZE * SIZE> board = {};

    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i++) {
            auto l = mkPoint(i, j);
            for (auto &p : inputs) {
                board[i + j * SIZE] += dist(p, l);
                if (board[i + j * SIZE] >= MAX_DIST) {
                    board[i + j * SIZE] = MAX_DIST + 5;
                    break;
                }
            }
        }
    }

    size_t count = 0;
    for (auto j = 0u; j < SIZE; j++) {
        for (auto i = 0u; i < SIZE; i++) {
            if (board[i + j * SIZE] < MAX_DIST) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    std::vector<Point> inputs;
    unsigned short x, y;
    while (std::cin >> x >> y) {
        inputs.push_back(std::make_pair(x, y));
    }

    std::cout << "Part1: " << part1(inputs) << std::endl;
    std::cout << "Part2: " << part2(inputs) << std::endl;
}
