

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <format>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <ranges>
#include <regex>


struct Connection {
    //unsigned p1, p2;
    std::string p1, p2;
    bool operator==(const Connection&) const = default;
    friend auto format_as(const Connection &c) {
        return fmt::format("({}-{})", c.p1, c.p2);
    }
};
//using Connection = std::pair<unsigned, unsigned>;

using List = std::map<std::string, std::set<std::string>>;

auto find_inter_connected(const List& list) {
    auto res = std::vector<std::set<std::string>>{};
    for (auto &[p, l] : list) {
        for (auto &p2 : l) {
            for (auto &p3 : list.at(p2)) {
                if (l.contains(p3))
                    res.emplace_back(std::set{p, p2, p3});
            }
        }
    }
    std::ranges::sort(res, [](const auto &a, const auto &b) {
            auto ita = a.begin();
            auto itb = b.begin();

            return *ita < *itb
            or (*ita == *itb) and (*std::next(ita) < *std::next(itb))
            or (*ita == *itb) and (*std::next(ita) == *std::next(itb)) and (*std::next(ita, 2) < *std::next(itb, 2));
            });
    res.erase(std::unique(res.begin(), res.end()), res.end());
    return res;
}


bool clique_is_in_nodes(const std::set<std::string>& clique, const std::set<std::string>& nodes) {
    for (auto &n : clique) {
        if (not nodes.contains(n)) return false;
    }
    return true;
}

auto find_max(const List &list) {

    std::set<std::string> best_clique;
    auto test_list = list;
    while (not test_list.empty()) {
        std::set<std::string> clique;
        for (auto &[p2, l2]  : test_list) {
            if (clique_is_in_nodes(clique, l2))
                clique.insert(p2);  
        }
        if (best_clique.size() < clique.size())
            best_clique = clique;
        test_list.erase(test_list.begin());
    }
    return best_clique;
}


int main() {

    auto list = List{};
    auto input = std::string{};
    std::regex r(R"(^([^-]+)-([^-]+)$)");
    std::smatch sm;
    while (getline(std::cin, input)) {
        regex_search(input, sm, r);
        auto p1 = sm[1].str();
        auto p2 = sm[2].str();
        list[p1].insert(p2);
        list[p2].insert(p1);
    }
    fmt::print("List is:\n{}\n", list);
    auto inter = find_inter_connected(list);
    fmt::print("Inter is:\n{}\n", fmt::join(inter, "\n"));

    auto sum = 0;
    for (auto &s : inter) {
        auto it = s.begin();
        if ((*it)[0] == 't' or (*std::next(it))[0] == 't' or (*std::next(it, 2))[0] == 't') sum++;
    }
    fmt::print("Sum is: {}\n", sum);

    auto best = find_max(list);
    fmt::print("Best clique is:\n{}\n{}\n", fmt::join(best, ","), best.size());
}
