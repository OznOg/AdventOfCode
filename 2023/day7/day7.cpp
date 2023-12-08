#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>



const auto cardstrength = std::map<char, unsigned>{
    std::make_pair<char, unsigned>('A', 14),
    { 'K', 13 },
    { 'Q', 12 },
    { 'J', 1 },
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

using Hand = std::vector<std::pair<char, unsigned>>;

using Data = std::vector<std::tuple<Hand, unsigned, std::string>>;


unsigned scoreHand(const Hand &hand) {
  if (hand.size() == 1) return 7; // Five of a kind
  if (hand.size() == 2 && hand[0].second == 4) { // Four of a kind
      if (hand[0].first == 'J' || hand[1].first == 'J')
          return 7; // upgrate to Five of a kind
      else
          return 6;
  }
  if (hand.size() == 2 && hand[0].second == 3) { // Full house
      if (hand[0].first == 'J' || hand[1].first == 'J')
          return 7; // upgrate to Five of a kind
      else
          return 5;
  }
  if (hand.size() == 3 && hand[0].second == 3) { // Three of a kind
      if (hand[0].first == 'J' || hand[1].first == 'J' || hand[2].first == 'J')
          return 6; // upgrate to Four of a kind
      else
          return 4;
  }
  if (hand.size() == 3 && hand[0].second == 2 && hand[1].second == 2) { // two pairs
      if (hand[0].first == 'J' || hand[1].first == 'J')
          return 6; // upgrate to Four of a kind
      else if (hand[2].first == 'J')
          return 5; // upgrate to Full house
      else
          return 3; // Two pair
  }
  if (hand.size() == 4 && hand[0].second == 2) { // One pair
      if (hand[0].first == 'J' || hand[1].first == 'J' || hand[2].first == 'J' || hand[3].first == 'J')
          return 4; // upgrate to Three of a kind
      else
          return 2;
  }
  if (hand.size() == 5) { // High card
      if (hand[0].first == 'J' || hand[1].first == 'J' || hand[2].first == 'J' || hand[3].first == 'J' || hand[4].first == 'J')
          return 2; // upgrate to One pair
      else
          return 1;
  }
  throw "WTF";
}

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

       data.emplace_back(std::make_tuple(std::move(hand), bid, cards));

    }

    std::sort(data.begin(), data.end(), [](auto &l, auto &r) {
                 auto &[hand1, bid1, orig1] = l; 
                 auto &[hand2, bid2, orig2] = r; 

                 if (scoreHand(hand1) == scoreHand(hand2)) {
                           for (auto i = 0; i < orig1.size(); i++) {
                              if (cardstrength.at(orig1[i]) == cardstrength.at(orig2[i]))
                                 continue;
                              return cardstrength.at(orig1[i]) < cardstrength.at(orig2[i]);
                           }
                 }
                 return scoreHand(hand1) < scoreHand(hand2);
            });

    for (auto &[h, b, original] : data) {
         std::cout << original << '\n'; 
    }

    unsigned winnings = 0;
    for (auto i = 0; i < data.size(); i++) {
        winnings += (i + 1) * std::get<1>(data[i]);
    }
    std::cout << "winnings are: " << winnings << '\n';
}

