#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>



const auto cardstrength = std::map<char, unsigned>{
    std::make_pair<char, unsigned>('A', 14),
    { 'K', 13 },
    { 'Q', 12 },
    { 'J', 11 },
    { 'T', 10 },
    { '9', 9 },
    { '8', 8 },
    { '7', 7 },
    { '6', 6 },
    { '5', 5 },
    { '4', 4 },
    { '3', 3 },
    { '2', 2 }
};

using HandValue = std::pair<unsigned, unsigned>;

using Hand = std::vector<std::pair<char, unsigned>>;

using Data = std::vector<std::pair<Hand, unsigned>>;



int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       auto cards = std::string{};
       auto bid = unsigned{};
       auto ss = std::stringstream{input};
       ss >> cards >> bid;

       auto group = std::map<char, unsigned>{};
       for (const auto &c : cards) {
           group[c]++;
       }
       Hand hand;
       for (const auto &e : group) {
           hand.emplace_back(e);
       }

       std::sort(hand.begin(), hand.end(), [](auto &l, auto &r) { return l.second >= r.second && (l.second != r.second || cardstrength.at(l.first) >= cardstrength.at(r.first)); });

       data.emplace_back(std::make_pair(std::move(hand), bid));

    }

    std::sort(data.begin(), data.end(), [](auto &l, auto &r) {
                 auto &[hand1, bid1] = l; 
                 auto &[hand2, bid2] = r; 

                 if (hand1.size() > hand2.size()) return true;
                 if (hand1.size() == hand2.size()) {
                    for (auto i = 0; i < hand1.size(); i++) {
                      if (hand1[i].second == hand2[i].second && cardstrength.at(hand1[i].first) == cardstrength.at(hand2[i].first))
                          continue;
                      if (hand1[i].second < hand2[i].second) return true;
                      if (hand1[i].second == hand2[i].second && cardstrength.at(hand1[i].first) < cardstrength.at(hand2[i].first)) return true;
                      return false;
                    }
                 }
                 return false;

            });

    unsigned winnings = 0;
    for (auto i = 0; i < data.size(); i++) {
        winnings += (i + 1) * data[i].second;
    }
    std::cout << "winnings are: " << winnings << '\n';
}

