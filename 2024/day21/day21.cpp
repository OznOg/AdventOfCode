

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

using Digicode = std::map<unsigned char, std::map<unsigned char, std::string>>;
using Digicode2 = std::map<unsigned char, std::map<unsigned char, std::vector<std::string>>>;

auto init_digicode() {
    auto digicode = Digicode{};
    digicode['0']['0'] = {"A"};
    digicode['0']['1'] = { "^<A" };
    digicode['0']['2'] = { "^A" };
    digicode['0']['3'] = { "^>A" };
    digicode['0']['4'] = { "^^<A" };
    digicode['0']['5'] = { "^^A" }; 
    digicode['0']['6'] = { "^^>A" };
    digicode['0']['7'] = { "^^^<A" };
    digicode['0']['8'] = { "^^^A" };
    digicode['0']['9'] = { "^^^>A" };
    digicode['0']['A'] = { ">A" };

    digicode['1']['0'] = { ">vA"             };
    digicode['1']['1'] = { "A"                     };
    digicode['1']['2'] = { ">A"                  };
    digicode['1']['3'] = { ">>A"             };
    digicode['1']['4'] = { "^A"                  };
    digicode['1']['5'] = { "^>A"             };
    digicode['1']['6'] = { "^>>A"        };
    digicode['1']['7'] = { "^^A"             };
    digicode['1']['8'] = { "^^>A"        };
    digicode['1']['9'] = { "^^>>A"   };
    digicode['1']['A'] = { ">>vA"        };

    digicode['2']['0'] = { "vA"             };
    digicode['2']['1'] = { "<A"                    };
    digicode['2']['2'] = { "A"                  };
    digicode['2']['3'] = { ">A"             };
    digicode['2']['4'] = { "^<A"                  };
    digicode['2']['5'] = { "^A"             };
    digicode['2']['6'] = { "^>A"        };
    digicode['2']['7'] = { "^^<A"             };
    digicode['2']['8'] = { "^^A"        };
    digicode['2']['9'] = { "^^>A"   };
    digicode['2']['A'] = { ">vA"        };

    digicode['3']['0'] = {"<vA"};
    digicode['3']['1'] = {"<<A"};
    digicode['3']['2'] = {"<A"};
    digicode['3']['3'] = {"A"};
    digicode['3']['4'] = {"<<^A"};
    digicode['3']['5'] = {"<^A"};
    digicode['3']['6'] = {"^A"};
    digicode['3']['7'] = {"<<^^A"};
    digicode['3']['8'] = {"<^^A"};
    digicode['3']['9'] = {"^^A"};
    digicode['3']['A'] = {"vA"};

    digicode['4']['0'] = {">vvvA"};
    digicode['4']['1'] = {"vA"};
    digicode['4']['2'] = {"v>A"};
    digicode['4']['3'] = {"v>>A"};
    digicode['4']['4'] = {"A"};
    digicode['4']['5'] = {">A"};
    digicode['4']['6'] = {">>A"};
    digicode['4']['7'] = {"^A"};
    digicode['4']['8'] = {"^>A"};
    digicode['4']['9'] = {"^>>A"};
    digicode['4']['A'] = {">>vvA"};

    digicode['5']['0'] = {"vvA"};
    digicode['5']['1'] = {"v<A"};
    digicode['5']['2'] = {"vA"};
    digicode['5']['3'] = {"v>A"};
    digicode['5']['4'] = {"<A"};
    digicode['5']['5'] = {"A"};
    digicode['5']['6'] = {">A"};
    digicode['5']['7'] = {"<^A"};
    digicode['5']['8'] = {"^A"};
    digicode['5']['9'] = {"^>A"};
    digicode['5']['A'] = {"vv>A"};

    digicode['6']['0'] = {"<vvA"};
    digicode['6']['1'] = {"<<vA"};
    digicode['6']['2'] = {"<vA"};
    digicode['6']['3'] = {"vA"};
    digicode['6']['4'] = {"<<A"};
    digicode['6']['5'] = {"<A"};
    digicode['6']['6'] = {"A"};
    digicode['6']['7'] = {"<<^A"};
    digicode['6']['8'] = {"<^A"};
    digicode['6']['9'] = {"^A"};
    digicode['6']['A'] = {"vvA"};

    digicode['7']['0'] = {">vvvA"};
    digicode['7']['1'] = {"vvA"};
    digicode['7']['2'] = {"vv>A"};
    digicode['7']['3'] = {"vv>>A"};
    digicode['7']['4'] = {"vA"};
    digicode['7']['5'] = {"v>A"};
    digicode['7']['6'] = {"v>>A"};
    digicode['7']['7'] = {"A"};
    digicode['7']['8'] = {">A"};
    digicode['7']['9'] = {">>A"};
    digicode['7']['A'] = {">>vvvA"};

    digicode['8']['0'] = {"vvvA"};
    digicode['8']['1'] = {"vv<<A"};
    digicode['8']['2'] = {"vvA"};
    digicode['8']['3'] = {"vv>A"};
    digicode['8']['4'] = {"v<A"};
    digicode['8']['5'] = {"vA"};
    digicode['8']['6'] = {"v>A"};
    digicode['8']['7'] = {"<A"};
    digicode['8']['8'] = {"A"};
    digicode['8']['9'] = {">A"};
    digicode['8']['A'] = {"vvv>A"};


    digicode['9']['0'] = {"vvv<A"};
    digicode['9']['1'] = {"<<vvA"};
    digicode['9']['2'] = {"<vvA"};
    digicode['9']['3'] = {"vvA"};
    digicode['9']['4'] = {"v<<A"};
    digicode['9']['5'] = {"v<A"};
    digicode['9']['6'] = {"vA"};
    digicode['9']['7'] = {"<<A"};
    digicode['9']['8'] = {"<A"};
    digicode['9']['9'] = {"A"};
    digicode['9']['A'] = {"vvvA"};

    digicode['A']['0'] = { "<A"                       };
    digicode['A']['1'] = { "^<<A"             };
    digicode['A']['2'] = { "^<A"                  };
    digicode['A']['3'] = { "^A"                       };
    digicode['A']['4'] = { "^^<<A"        };
    digicode['A']['5'] = { "^^<A"             };
    digicode['A']['6'] = { "^^A"                  };
    digicode['A']['7'] = { "^^^<<A"   };
    digicode['A']['8'] = { "^^^<A"        };
    digicode['A']['9'] = { "^^^A"             };
    digicode['A']['A'] = { "A"                          };

    return digicode;
}

auto init_digicode2() {
    auto digicode = Digicode2{};

    digicode['0']['0'] = { "A" };
    digicode['0']['1'] = { "^<A" };
    digicode['0']['2'] = { "^A" };
    digicode['0']['3'] = { ">^A", "^>A" };
    digicode['0']['4'] = { "^<^A", "^^<A" };
    digicode['0']['5'] = { "^^A" };
    digicode['0']['6'] = { ">^^A", "^>^A", "^^>A" };
    digicode['0']['7'] = { "^<^^A", "^^<^A", "^^^<A" };
    digicode['0']['8'] = { "^^^A" };
    digicode['0']['9'] = { ">^^^A", "^>^^A", "^^>^A", "^^^>A" };
    digicode['0']['A'] = { ">A" };
    digicode['1']['0'] = { ">vA" };
    digicode['1']['1'] = { "A" };
    digicode['1']['2'] = { ">A" };
    digicode['1']['3'] = { ">>A" };
    digicode['1']['4'] = { "^A" };
    digicode['1']['5'] = { ">^A", "^>A" };
    digicode['1']['6'] = { ">>^A", ">^>A", "^>>A" };
    digicode['1']['7'] = { "^^A" };
    digicode['1']['8'] = { ">^^A", "^>^A", "^^>A" };
    digicode['1']['9'] = { ">>^^A", ">^>^A", ">^^>A", "^>>^A", "^>^>A", "^^>>A" };
    digicode['1']['A'] = { ">>vA", ">v>A" };
    digicode['2']['0'] = { "vA" };
    digicode['2']['1'] = { "<A" };
    digicode['2']['2'] = { "A" };
    digicode['2']['3'] = { ">A" };
    digicode['2']['4'] = { "<^A", "^<A" };
    digicode['2']['5'] = { "^A" };
    digicode['2']['6'] = { ">^A", "^>A" };
    digicode['2']['7'] = { "<^^A", "^<^A", "^^<A" };
    digicode['2']['8'] = { "^^A" };
    digicode['2']['9'] = { ">^^A", "^>^A", "^^>A" };
    digicode['2']['A'] = { ">vA", "v>A" };
    digicode['3']['0'] = { "<vA", "v<A" };
    digicode['3']['1'] = { "<<A" };
    digicode['3']['2'] = { "<A" };
    digicode['3']['3'] = { "A" };
    digicode['3']['4'] = { "<<^A", "<^<A", "^<<A" };
    digicode['3']['5'] = { "<^A", "^<A" };
    digicode['3']['6'] = { "^A" };
    digicode['3']['7'] = { "<<^^A", "<^<^A", "<^^<A", "^<<^A", "^<^<A", "^^<<A" };
    digicode['3']['8'] = { "<^^A", "^<^A", "^^<A" };
    digicode['3']['9'] = { "^^A" };
    digicode['3']['A'] = { "vA" };
    digicode['4']['0'] = { ">vvvA", "v>vvA", "vvv>A" };
    digicode['4']['1'] = { "vA" };
    digicode['4']['2'] = { ">vA", "v>A" };
    digicode['4']['3'] = { ">>vA", ">v>A", "v>>A" };
    digicode['4']['4'] = { "A" };
    digicode['4']['5'] = { ">A" };
    digicode['4']['6'] = { ">>A" };
    digicode['4']['7'] = { "^A" };
    digicode['4']['8'] = { ">^A", "^>A" };
    digicode['4']['9'] = { ">>^A", ">^>A", "^>>A" };
    digicode['4']['A'] = { ">>vvA", ">v>vA", ">vv>A", "v>>vA", "v>v>A" };
    digicode['5']['0'] = { "vvA" };
    digicode['5']['1'] = { "<vA", "v<A" };
    digicode['5']['2'] = { "vA" };
    digicode['5']['3'] = { ">vA", "v>A" };
    digicode['5']['4'] = { "<A" };
    digicode['5']['5'] = { "A" };
    digicode['5']['6'] = { ">A" };
    digicode['5']['7'] = { "<^A", "^<A" };
    digicode['5']['8'] = { "^A" };
    digicode['5']['9'] = { ">^A", "^>A" };
    digicode['5']['A'] = { ">vvA", "v>vA", "vv>A" };
    digicode['6']['0'] = { "<vvA", "v<vA", "vv<A" };
    digicode['6']['1'] = { "<<vA", "<v<A", "v<<A" };
    digicode['6']['2'] = { "<vA", "v<A" };
    digicode['6']['3'] = { "vA" };
    digicode['6']['4'] = { "<<A" };
    digicode['6']['5'] = { "<A" };
    digicode['6']['6'] = { "A" };
    digicode['6']['7'] = { "<<^A", "<^<A", "^<<A" };
    digicode['6']['8'] = { "<^A", "^<A" };
    digicode['6']['9'] = { "^A" };
    digicode['6']['A'] = { "vvA" };
    digicode['7']['0'] = { ">vvvA", "v>vvA", "vv>vA" };
    digicode['7']['1'] = { "vvA" };
    digicode['7']['2'] = { ">vvA", "v>vA", "vv>A" };
    digicode['7']['3'] = { ">>vvA", ">v>vA", ">vv>A", "v>>vA", "v>v>A", "vv>>A" };
    digicode['7']['4'] = { "vA" };
    digicode['7']['5'] = { ">vA", "v>A" };
    digicode['7']['6'] = { ">>vA", ">v>A", "v>>A" };
    digicode['7']['7'] = { "A" };
    digicode['7']['8'] = { ">A" };
    digicode['7']['9'] = { ">>A" };
    digicode['7']['A'] = { ">>vvvA", ">v>vvA", ">vv>vA", ">vvv>A", "v>>vvA", "v>v>vA", "v>vv>A", "vv>>vA", "vv>v>A" };
    digicode['8']['0'] = { "vvvA" };
    digicode['8']['1'] = { "<<vvA", "<v<vA", "<vv<A", "v<<vA", "v<v<A", "vv<<A" };
    digicode['8']['2'] = { "vvA" };
    digicode['8']['3'] = { ">vvA", "v>vA", "vv>A" };
    digicode['8']['4'] = { "<vA", "v<A" };
    digicode['8']['5'] = { "vA" };
    digicode['8']['6'] = { ">vA", "v>A" };
    digicode['8']['7'] = { "<A" };
    digicode['8']['8'] = { "A" };
    digicode['8']['9'] = { ">A" };
    digicode['8']['A'] = { ">vvvA", "v>vvA", "vv>vA", "vvv>A" };
    digicode['9']['0'] = { "<vvvA", "v<vvA", "vv<vA", "vvv<A" };
    digicode['9']['1'] = { "<<vvA", "<v<vA", "<vv<A", "v<<vA", "v<v<A", "vv<<A" };
    digicode['9']['2'] = { "<vvA", "v<vA", "vv<A" };
    digicode['9']['3'] = { "vvA" };
    digicode['9']['4'] = { "<<vA", "<v<A", "v<<A" };
    digicode['9']['5'] = { "<vA", "v<A" };
    digicode['9']['6'] = { "vA" };
    digicode['9']['7'] = { "<<A" };
    digicode['9']['8'] = { "<A" };
    digicode['9']['9'] = { "A" };
    digicode['9']['A'] = { "vvvA" };
// +---+---+---+
// | 7 | 8 | 9 |
// +---+---+---+
// | 4 | 5 | 6 |
// +---+---+---+
// | 1 | 2 | 3 |
// +---+---+---+
//     | 0 | A |
//     +---+---+
    digicode['A']['0'] = { "<A" };
    digicode['A']['1'] = { "<^<A", "^<<A" };
    digicode['A']['2'] = { "<^A", "^<A" };
    digicode['A']['3'] = { "^A" };
    digicode['A']['4'] = { "<^<^A", "<^^<A", "^<<^A", "^<^<A", "^^<<A" };
    digicode['A']['5'] = { "<^^A", "^<^A", "^^<A" };
    digicode['A']['6'] = { "^^A" };
    digicode['A']['7'] = { "<^<^^A", "<^^<^A", "<^^^<A", "^<<^^A", "^<^<^A", "^<^^<A", "^^<<^A", "^^<^<A", "^^^<<A" };
    digicode['A']['8'] = { "<^^^A", "^<^^A", "^^<^A", "^^^<A" };
    digicode['A']['9'] = { "^^^A" };
    digicode['A']['A'] = { "A" };

    return digicode;
}

auto init_keypad() {
    auto keypad = Digicode{};

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

    keypad['<']['>'] = {">>A"};
    keypad['<']['^'] = {">^A"};
    keypad['<']['v'] = {">A"};
    keypad['<']['A'] = {">>^A"};
    keypad['<']['<'] = {"A"};

    keypad['A']['>'] = {"vA"};
    keypad['A']['^'] = {"<A"};
    keypad['A']['v'] = {"<vA"};
    keypad['A']['A'] = {"A"};
    keypad['A']['<'] = {"v<<A"};

    keypad['>']['>'] = {"A"};
    keypad['>']['^'] = {"<^A"};
    keypad['>']['v'] = {"<A"};
    keypad['>']['A'] = {"^A"};
    keypad['>']['<'] = {"<<A"};

    keypad['v']['>'] = {">A"};
    keypad['v']['^'] = {"^A"};
    keypad['v']['v'] = {"A"};
    keypad['v']['A'] = {">^A"};
    keypad['v']['<'] = {"<A"};

    keypad['^']['>'] = {">vA"};
    keypad['^']['^'] = {"A"};
    keypad['^']['v'] = {"vA"};
    keypad['^']['A'] = {">A"};
    keypad['^']['<'] = {"v<A"};

    return keypad;
}
 
auto init_keypad2() {
    auto keypad = Digicode2{};

    //     +---+---+
    //     | ^ | A |
    // +---+---+---+
    // | < | v | > |
    // +---+---+---+

    keypad['<']['<'] = { "A" };
    keypad['<']['>'] = { ">>A" };
    keypad['<']['A'] = { ">>^A", ">^>A" };
    keypad['<']['^'] = { ">^A" };
    keypad['<']['v'] = { ">A" };
    keypad['>']['<'] = { "<<A" };
    keypad['>']['>'] = { "A" };
    keypad['>']['A'] = { "^A" };
    keypad['>']['^'] = { "<^A", "^<A" };
    keypad['>']['v'] = { "<A" };
    keypad['A']['<'] = { "<v<A", "v<<A" };
    keypad['A']['>'] = { "vA" };
    keypad['A']['A'] = { "A" };
    keypad['A']['^'] = { "<A" };
    keypad['A']['v'] = { "<vA", "v<A" };
    keypad['^']['<'] = { "v<A" };
    keypad['^']['>'] = { ">vA", "v>A" };
    keypad['^']['A'] = { ">A" };
    keypad['^']['^'] = { "A" };
    keypad['^']['v'] = { "vA" };
    keypad['v']['<'] = { "<A" };
    keypad['v']['>'] = { ">A" };
    keypad['v']['A'] = { ">^A", "^>A" };
    keypad['v']['^'] = { "^A" };
    keypad['v']['v'] = { "A" };

    return keypad;
}

std::vector<std::string> scramble(std::string s) {
    if (s.size() == 1) return { s };

    auto scrambled = std::vector<std::string>{};
    for (auto i = 0; i < s.size(); i++) {
       auto c = s[i];
       auto s2 = s;
       s2.erase(i, 1);
       for (auto &ss : scramble(s2)) {
          scrambled.emplace_back(std::string(1, c) + ss);
       }
    }
    return scrambled;
}

const Digicode2 digicode2 = init_digicode2();
const Digicode2 keypad2 = init_keypad2();


std::string compute3(const std::string& code, unsigned char curr, const std::string& test = "") {
    if (code.size() == 0) {
       return test;
    }
   
    std::string best(1000, '#');
    for (auto& s : keypad2.at(curr).at(code[0])) {
       auto sub = compute3(code.substr(1, std::string::npos), code[0], test + s);
       if (sub.size() < best.size()) best = sub;
    }
    return best;
}

std::string compute2(const std::string& code, unsigned char curr, const std::string& test = "") {
    if (code.size() == 0) {
       return compute3(test, 'A');
    }
   
    std::string best(1000, '#');
    for (auto& s : keypad2.at(curr).at(code[0])) {
       auto sub = compute2(code.substr(1, std::string::npos), code[0], test + s);
       if (sub.size() < best.size()) best = sub;
    }
    return best;
}

std::string compute1(const std::string& code, unsigned char curr, const std::string& test = "") {
    if (code.size() == 0) {
       return compute2(test, 'A');
    }
   
    std::string best(1000, '#');
    for (auto& s : digicode2.at(curr).at(code[0])) {
       auto sub = compute1(code.substr(1, std::string::npos), code[0], test + s);
       if (sub.size() < best.size()) best = sub;
    }
    return best;
}

int main() {

  auto codes = std::vector<std::string>{};
  auto input = std::string{};
  while (getline(std::cin, input)) {
      codes.emplace_back(input);
  }
  fmt::print("Codes are:\n{}\n", codes);

  const auto digicode = init_digicode();
  const auto keypad = init_keypad();

//  for (auto &[from, mapto] : digicode) {
//      for (auto [to, string] : mapto) {
//          string.resize(string.size() - 1);
//          auto scram = scramble(string);
//          std::ranges::sort(scram);
//          scram.erase( std::unique( scram.begin(), scram.end() ), scram.end() );
//
//          digicode2[from][to] = scram;
//      }
//  }
//  for (auto &[from, mapto] : digicode2) {
//      for (auto [to, stringv] : mapto) {
//          fmt::print("digicode['{}']['{}'] = {{ \"{}A\" }};\n", (char)from, (char) to, fmt::join(stringv, "A\", \""));
//      }
//  }
//  for (auto &[from, mapto] : keypad) {
//      for (auto [to, string] : mapto) {
//          string.resize(string.size() - 1);
//          auto scram = scramble(string);
//          std::ranges::sort(scram);
//          scram.erase( std::unique( scram.begin(), scram.end() ), scram.end() );
//
//          keypad2[from][to] = scram;
//      }
//  }
//  for (auto &[from, mapto] : keypad2) {
//      for (auto [to, stringv] : mapto) {
//          fmt::print("keypad2['{}']['{}'] = {{ \"{}A\" }};\n", (char)from, (char) to, fmt::join(stringv, "A\", \""));
//      }
//  }

  auto sum = 0;
  for (const auto &code: codes) {
      fmt::print("Code {}: ", code);
      auto best = compute1(code, 'A', "");
      fmt::print("best {}\n", best);
      sum += best.size() * stol(code.substr(0, 4));
  }
  fmt::print("Sum is: {}\n", sum); 
}


