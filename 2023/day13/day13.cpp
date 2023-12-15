#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <set>
#include <optional>

using Line = std::string;
using Data = std::vector<std::vector<Line>>;

auto test_maybe_horizontal_mirror(const std::vector<Line> &v) -> std::optional<unsigned> {

    auto possible = std::set<unsigned>{};
    for (auto i = 0u; i < v.front().size() -1 ; i++) {
       possible.insert(i);
    }

    auto is_h_symetry_at = [] (auto &lines, unsigned idx) {
        bool maybe = false;
        for (auto &l : lines) {
            for (auto j = 0; j <= std::min<unsigned>(idx, l.size() - 1 - (idx + 1)); j++) {
               if (l[idx-j] != l[idx + j + 1]) {
                   if (!maybe) {
                       maybe = true;
                       continue;
                   } else
                       return false;
               }
            }
        }
        return maybe;
    };


    for (auto i = 0u; i < v.front().size() -1 ; i++) {
       if (not is_h_symetry_at(v, i))
          possible.erase(i);
    }

    if (possible.size() >= 2)
       throw "WTF";

    if (possible.size() == 0)
       return {};
       
    return *possible.begin() + 1;
}

auto test_maybe_vertical_mirror(const std::vector<Line> &v) -> std::optional<unsigned> {

    auto possible = std::set<unsigned>{};
    for (auto i = 0u; i < v.size() -1 ; i++) {
       possible.insert(i);
    }

    auto is_v_symetry_at = [] (auto &lines, unsigned idx) {
        bool maybe = false;
        for (auto j = 0; j <= std::min<unsigned>(idx, lines.size() -1 - (idx + 1)); j++) {
            for (auto i = 0; i < lines.front().size(); i++) {
                if (lines[idx-j][i] != lines[idx + j + 1][i]) {
                   if (!maybe) {
                       maybe = true;
                       continue;
                   } else
                       return false;
                }
            }
        }
        return maybe;
    };


    for (auto i = 0u; i < v.size() -1 ; i++) {
       if (not is_v_symetry_at(v, i))
          possible.erase(i);
    }

    if (possible.size() >= 2)
       throw "WTF";

    if (possible.size() == 0)
       return {};
       
    return *possible.begin() + 1;
}

auto maybe_do_the_job(const std::vector<Line> &v) {

    auto h_mirror = test_maybe_horizontal_mirror(v);
    if (h_mirror) {
       return std::make_pair(true, *h_mirror);
    }
    
    auto v_mirror = test_maybe_vertical_mirror(v);
    if (v_mirror) {
       return std::make_pair(false, *v_mirror);
    }
    throw "WTF";
}

auto test_horizontal_mirror(const std::vector<Line> &v) -> std::optional<unsigned> {

    auto possible = std::set<unsigned>{};
    for (auto i = 0u; i < v.front().size() -1 ; i++) {
       possible.insert(i);
    }

    auto is_h_symetry_at = [] (auto &lines, unsigned idx) {
        for (auto &l : lines) {
            for (auto j = 0; j <= std::min<unsigned>(idx, l.size() - 1 - (idx + 1)); j++) {
               if (l[idx-j] != l[idx + j + 1])
                  return false;
            }
        }
        return true;
    };


    for (auto i = 0u; i < v.front().size() -1 ; i++) {
       if (not is_h_symetry_at(v, i))
          possible.erase(i);
    }

    if (possible.size() >= 2)
       throw "WTF";

    if (possible.size() == 0)
       return {};
       
    return *possible.begin() + 1;
}

auto test_vertical_mirror(const std::vector<Line> &v) -> std::optional<unsigned> {

    auto possible = std::set<unsigned>{};
    for (auto i = 0u; i < v.size() -1 ; i++) {
       possible.insert(i);
    }

    auto is_v_symetry_at = [] (auto &lines, unsigned idx) {
        for (auto j = 0; j <= std::min<unsigned>(idx, lines.size() -1 - (idx + 1)); j++) {
            if (lines[idx-j] != lines[idx + j + 1])
                return false;
        }
        return true;
    };


    for (auto i = 0u; i < v.size() -1 ; i++) {
       if (not is_v_symetry_at(v, i))
          possible.erase(i);
    }

    if (possible.size() >= 2)
       throw "WTF";

    if (possible.size() == 0)
       return {};
       
    return *possible.begin() + 1;
}

auto do_the_job(const std::vector<Line> &v) {

    auto h_mirror = test_horizontal_mirror(v);
    if (h_mirror) {
       return std::make_pair(true, *h_mirror);
    }
    
    auto v_mirror = test_vertical_mirror(v);
    if (v_mirror) {
       return std::make_pair(false, *v_mirror);
    }
    throw "WTF";
}

int main() {

    auto data = Data{};

    data.resize(1);
    auto input = std::string{};
    while (getline(std::cin, input)) {
        if (input.empty()) {
            data.resize(data.size() + 1);
            continue;
        }
        data.back().emplace_back(input);
    }

    unsigned sum = 0;
    for (auto &e : data) {
        auto res = do_the_job(e);
        if (res.first)
           sum += res.second;
        else 
           sum += res.second * 100;

    }
    std::cout << "Sum is: " << sum << '\n';

    sum = 0;
    for (auto &e : data) {
        auto res = maybe_do_the_job(e);
        if (res.first)
           sum += res.second;
        else 
           sum += res.second * 100;

    }
    std::cout << "Maybe sum is: " << sum << '\n';
}


