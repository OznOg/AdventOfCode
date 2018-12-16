
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unistd.h>

using Pos = std::pair<size_t, size_t>;
enum class Heading : char { U, D, R, L };

struct Kart {
    Heading h;
    Pos p;
    enum class Dir { S, L, R } next;
};
struct Cmp {
    bool operator()(const Kart &a, const Kart &b) {
        auto &pa = a.p;
        auto &pb = b.p;
        if (pa.second == pb.second)
            return pa.first < pb.first;
        return pa.second < pb.second;
    }
};
using Map = std::vector<std::string>;

auto fixMap(Map &map) {
    std::set<Kart, Cmp> karts;
    for (auto j = size_t(); j < map.size(); j++) {
        auto &line = map[j];
        for (auto i = size_t(); i < line.size(); i++) {
           auto &c = line[i];
           switch (c) {
               case '<':
               case '>': {
                             auto h = c == '>' ? Heading::R : Heading::L;
                             karts.insert({h, std::make_pair(i, j), Kart::Dir::L});
                             c = '-';
                         }
                  break;
               
               case '^':
               case 'v': {
                             auto h = c == 'v' ? Heading::D : Heading::U;
                             karts.insert({h, std::make_pair(i, j), Kart::Dir::L});
                             c = '|';
                         }
                  break;
               
               case '-':
               case '/':
               case '\\':
               case '|':
               case '+':
                  break;
           }
        }
    }
    return karts;
}

void display(const auto &karts, const Map &map) {
    auto copy = map;

    for (auto &k : karts) {
        copy[k.p.second][k.p.first] = 'O';
    }
    for (auto &line : copy)
        std::cout << line << std::endl;
}

Kart::Dir nextDir(Kart::Dir d) {
    switch(d) {
        case Kart::Dir::L:
            return Kart::Dir::S;
        case Kart::Dir::S:
            return Kart::Dir::R;
        case Kart::Dir::R:
            return Kart::Dir::L;
    }
    throw "gne"; // silent stupid gcc
}

Kart moveOne(Kart kart, const Map &map) {
     auto &pos = kart.p;
     auto &head = kart.h;
     switch (head) {
         case Heading::U:
             switch (map[pos.second - 1][pos.first]) {
                 case '-':
                     throw "impossible";
                 case '\\':
                     pos.second -= 1;
                     head = Heading::L;
                     break;
                 case '/':
                     pos.second -= 1;
                     head = Heading::R;
                     break;
                 case '|':
                     pos.second -= 1;
                     break;
                 case '+':
                     pos.second -= 1;
                     switch (kart.next) {
                         case Kart::Dir::L:
                             head = Heading::L;
                             break;
                         case Kart::Dir::S:
                             break;
                         case Kart::Dir::R:
                             head = Heading::R;
                             break;
                     }
                     kart.next = nextDir(kart.next);
                     break;
             }
             break;
         case Heading::D:
             switch (map[pos.second + 1][pos.first]) {
                 case '-':
                     throw "impossible";
                 case '\\':
                     pos.second += 1;
                     head = Heading::R;
                     break;
                 case '/':
                     pos.second += 1;
                     head = Heading::L;
                     break;
                 case '|':
                     pos.second += 1;
                     break;
                 case '+':
                     pos.second += 1;
                     switch (kart.next) {
                         case Kart::Dir::L:
                             head = Heading::R;
                             break;
                         case Kart::Dir::S:
                             break;
                         case Kart::Dir::R:
                             head = Heading::L;
                             break;
                     }
                     kart.next = nextDir(kart.next);
                     break;
             }
             break;
         case Heading::L:
             switch (map[pos.second][pos.first - 1]) {
                 case '-':
                     pos.first -= 1;
                     break;
                 case '\\':
                     pos.first -= 1;
                     head = Heading::U;
                     break;
                 case '/':
                     pos.first -= 1;
                     head = Heading::D;
                     break;
                 case '|':
                     throw "impossible";
                 case '+':
                     pos.first -= 1;
                     switch (kart.next) {
                         case Kart::Dir::L:
                             head = Heading::D;
                             break;
                         case Kart::Dir::S:
                             break;
                         case Kart::Dir::R:
                             head = Heading::U;
                             break;
                     }
                     kart.next = nextDir(kart.next);
                     break;
             }
             break;
         case Heading::R:
             switch (map[pos.second][pos.first + 1]) {
                 case '-':
                     pos.first += 1;
                     break;
                 case '\\':
                     pos.first += 1;
                     head = Heading::D;
                     break;
                 case '/':
                     pos.first += 1;
                     head = Heading::U;
                     break;
                 case '|':
                     throw "impossible";
                 case '+':
                     pos.first += 1;
                     switch (kart.next) {
                         case Kart::Dir::L:
                             head = Heading::U;
                             break;
                         case Kart::Dir::S:
                             break;
                         case Kart::Dir::R:
                             head = Heading::D;
                             break;
                     }
                     kart.next = nextDir(kart.next);
                     break;
             }
             break;
     }
     return kart;
}

auto _move(const std::set<Kart, Cmp> &karts, const Map &map) {
    std::set<Kart, Cmp> next; 
    for (auto &k : karts) {
        auto n = moveOne(k, map);
        if (next.find(k) != std::end(next) // original position already eached
            || next.find(n) != std::end(next)) { // or next position already reached
            //Kaboom
            std::cout << "Part 1: " << n.p.first << "," << n.p.second << std::endl;
            next.erase(n);
            next.erase(k);
        } else {
            next.insert(n);
        }
    }
    return next;
}

int main() {
    std::string line;

    Map map;
    while (getline(std::cin, line)) {
        map.push_back(std::move(line));
    }


   auto karts = fixMap(map);

   while (true) { 
       karts = _move(karts, map);

       if (karts.size() == 1) {
           auto &n = *karts.begin();
           std::cout << "Part 2: " << n.p.first << "," << n.p.second << std::endl;
       //    display(karts, map); 
           break;
       }
       if (karts.empty()) {
           std::cout << "Somethig went wrong..." << std::endl;
           break;
       }
       //sleep(1);
   }
}
