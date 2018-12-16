
#include <array>
#include <iomanip>
#include <iostream>
#include <tuple>
using Cell = std::pair<size_t, size_t>;

#define SERIAL 9435
#define SIZE 300

ssize_t power(const Cell &c) {
    auto rack_id = c.first + 10;
    ssize_t power_level = rack_id * c.second + SERIAL;
    power_level *= rack_id; 
    power_level = (power_level / 100) % 10;
    return power_level - 5;
}

using Grid = std::array<std::array<ssize_t, SIZE>, SIZE>;

auto compute() {
    Grid grid;
    for (auto i = size_t(); i < grid.size(); i++)
        for (auto j = size_t(); j < grid[i].size(); j++)
            grid[j][i] = power(std::make_pair(i + 1, j + 1));
    return grid;
}

void display(const Grid &g) {
    for (auto &col : g) {
        for (auto &e : col)
           std::cout << std::setw(4) << e;
        std::cout << std::endl;
    }
}

ssize_t value(const Grid &g, size_t x, size_t y, size_t size) {
    size_t val = 0;
    for (auto j = y; j < y + size; j++)
        for (auto i = x; i < x + size; i++)
            val += g[j][i];
    return val;
}

std::pair<Cell, ssize_t> findMax(const Grid &grid, size_t size) {
    Cell c = {};
    ssize_t max = 0;
    for (auto i = size_t(); i < grid.size() - size; i++)
        for (auto j = size_t(); j < grid[i].size() - size; j++) {
            auto m = value(grid, i, j, size);
            if (m > max) {
                max = m;
                c = std::make_pair(i + 1, j + 1);
            }
        }
    return std::make_pair(c, max);
}

std::pair<Cell, size_t> metaFindMax(const Grid &grid) {
    Cell c = {};
    ssize_t max = 0;
    size_t _size = 0;
    for (auto size = size_t(1); size <= SIZE; size++) {
        auto m = findMax(grid, size);
        if (m.second > max) {
            max = m.second;
            c = m.first;
            _size = size;
        }
    }
    return std::make_pair(c, _size);
}

int main() {
    auto grid = compute();
    //display(grid);
    Cell c;
    ssize_t max;
    std::tie(c, max) = findMax(grid, 3);

    std::cout << "Part1: " << c.first << "," << c.second << std::endl;

    size_t size;
    std::tie(c, size) = metaFindMax(grid);
    std::cout << "Part2: " << c.first << "," << c.second << "," << size << std::endl;
}
