

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


inline auto exp2(unsigned x) {
  return 1ull << x;
}

struct Computer {
  unsigned long long A = 0, B = 0, C = 0;

  unsigned ip = 0;

  std::vector<unsigned> output;
  struct Instr {
      unsigned code;
      unsigned op;
      friend auto format_as(const Instr &i) {
        return fmt::format("(code={}, op={})", i.code, i.op);
      }
  };
  std::vector<Instr> prog;

  friend auto format_as(const Computer &c) {
    return fmt::format("(A={}, B={}, C={}, ip={}, prog={})", c.A, c.B, c.C, c.ip, c.prog);
  }

  unsigned op2val(const unsigned &op) {
      switch (op) {
          case 0:
          case 1:
          case 2:
          case 3:
              return op;
          case 4:
              return A;
          case 5:
              return B;
          case 6:
              return C;
      }
      throw "WTF";
  }

  void run_special() {
    while (run_one() and output.size() <= prog.size() * 2)
      ;
  }
  void run() {
    while (run_one())
      ;
  }
  bool run_one() {
     if (ip >= prog.size()) return false;

     auto instr = prog.at(ip);
     switch (instr.code) {
         case 0: //adv
             A /= exp2(op2val(instr.op));
             ip++;
             break;
         case  1: // bxl
             B ^= instr.op;
             ip++;
             break;
         case 2: // bst
             B = op2val(instr.op) % 8;
             ip++;
             break;
         case 3: // jnz
             if (A != 0) {
                 if (instr.op % 2) throw "WTF";
                 ip = instr.op / 2;
             } else ip++;
             break;

         case 4: //bxc
             B ^= C;
             ip++;
             break;
         case 5: //out
             output.push_back(op2val(instr.op) % 8);
             ip++;
             break;

         case 6: // bdv
             B = A / exp2(op2val(instr.op));
             ip++;
             break;

         case 7: // cdv
             C = A / exp2(op2val(instr.op));
             ip++;
             break;
         default:
             throw "WTF";
     }
     return true;
  }
};


std::optional<unsigned long long> force(const Computer &cref, unsigned long long A, const int idx, std::vector<unsigned> output) {
  if (idx < 0) return A;
  A <<= 3;
  for (auto a = 0; a <= 7; a++) {
    auto computer = cref;
    computer.A = A | a;
    computer.run_special();
    if (std::equal(output.begin() + idx, output.end(), computer.output.begin())) {
      auto r = force(cref, A | a, idx - 1, output);
      if (r) return r;
    }
  }
  return {};
}

int main() {

  auto computer = Computer{};
  auto input = std::string{};
  std::regex r(R"((\d+))");
  std::smatch sm;
  getline(std::cin, input);
  regex_search(input, sm, r);
  computer.A = stol(sm[1].str());
  getline(std::cin, input);
  regex_search(input, sm, r);
  computer.B = stol(sm[1].str());
  getline(std::cin, input);
  regex_search(input, sm, r);
  computer.C = stol(sm[1].str());
  getline(std::cin, input); // empty line
  getline(std::cin, input);
  for (; regex_search(input, sm, r);) {
    auto code = stol(sm[1].str());
    input = sm.suffix();
    regex_search(input, sm, r);
    auto op = stol(sm[1].str());
    computer.prog.emplace_back(code, op);
    input = sm.suffix();
  }

  const auto cref = computer;

  fmt::print("Computer is:\n{}\n", computer);
  computer.run();
  fmt::print("Computer is:\n{}\n", computer);
  fmt::print("Output is:\n{}\n", fmt::join(computer.output, ","));

  auto prog = std::vector<unsigned>{};
  for (auto i : computer.prog) {
     prog.emplace_back(i.code); 
     prog.emplace_back(i.op); 
  }

  fmt::print("Prog is:\n{}\n", fmt::join(prog, ","));

  auto A = force(cref, 0, prog.size() - 1,  prog);
  fmt::print("A is:\n{}\n", A);
  computer = cref;
  computer.A = *A;
  computer.run_special();
  fmt::print("Output is:\n{}\n", fmt::join(computer.output, ","));
}


