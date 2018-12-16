
#include <array>
#include <vector>
#include <iostream>
#include <tuple>
#include <unistd.h>

struct Point {
    ssize_t x = 0, y = 0, vx = 0, vy = 0;
};

size_t abs(ssize_t p) {
    return p > 0 ? p : -p;
}

std::tuple<size_t, size_t, ssize_t, ssize_t> max_dist(const std::vector<Point> &inputs) {
    ssize_t maxx = 0, maxy = 0;
    ssize_t minx = 0xFFFFFFF, miny = 0xFFFFFFF;
    for (auto &p : inputs) {
        maxx = std::max(maxx, p.x);
        minx = std::min(minx, p.x);
        maxy = std::max(maxy, p.y);
        miny = std::min(miny, p.y);
    }
    return std::make_tuple(abs(maxx - minx), abs(maxy - miny), minx, miny);
}

bool display(const std::vector<Point> &inputs) {
    auto max = max_dist(inputs);
    if (std::get<1>(max) >= 188 && std::get<0>(max) >= 46) {
        return false;
    }
    std::array<std::array<bool, 188>, 46> screen = {};
    bool on_screen = false;
    for (auto &p : inputs) {
         auto y = p.y + 23 - std::get<3>(max);
         auto x = p.x + 90 - std::get<2>(max);
         if (y < 46 && y >= 0
             && x < 188 && x >= 0){
             screen[y][x] = true;
             on_screen = true;
         }
    }
    if (!on_screen)
        return false;

    for (auto &col : screen) {
        for (auto &b : col)
            std::cout << (b ? "#" : ".");
        std::cout << std::endl;
    }
    return true;
}

void tick(std::vector<Point> &inputs) {
    for (auto &p : inputs) {
         p.y += p.vy;
         p.x += p.vx;
    }
}

int main() {
    std::vector<Point> inputs;
    Point p;
    while (std::cin >> p.x >> p.y >> p.vx >> p.vy) {
        inputs.push_back(p);
    }

    size_t time = 0u;
    while (inputs[0].x < 20221) {
        auto see_smthing = display(inputs);
        if (see_smthing){
            std::cout << "Time: " << time << std::endl;
            sleep(1);
        }
        tick(inputs);
        time++;
    }
}
