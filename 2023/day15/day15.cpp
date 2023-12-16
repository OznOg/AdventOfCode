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
#include <list>
#include <numeric>

using Line = std::string;
using Data = std::vector<Line>;


unsigned char hash(const std::string &s) {
   unsigned h = 0;

   for (auto &c : s) {
         h += c;
         h *= 17;
         h %= 256;
   }
   
   return static_cast<unsigned char>(h);
}

using Box = std::list<std::pair<std::string, unsigned>>;
using Boxes = std::vector<Box>;

struct Instr {
    std::string label;
    unsigned char op;
    unsigned focal = -1;
};

auto parse_instr(const Data &data) -> std::vector<Instr> {
    auto instructions = std::vector<Instr>{};
    for (const auto &input : data) {
        auto pos = std::find_if(input.begin(), input.end(), [] (auto &&c) { return !std::isalpha(c); });
        auto inst = Instr{}; 
        inst.label = std::string(input.begin(), pos);
        inst.op = *pos;
        if (inst.op == '=')
            inst.focal = std::stoi(std::string(pos + 1, input.end()));
        instructions.emplace_back(std::move(inst));
    }
    return instructions;
}

std::string to_string(const Box &box) {
   auto ss = std::stringstream{}; 
   for (auto &[l, f] : box) {
      ss << "[" << l << " " << f << "]";
   }
   return ss.str();
}

auto run(Boxes &boxes, const std::vector<Instr> &instr) {
    for (auto &i : instr) {
       auto idx = hash(i.label);
       auto &box = boxes[idx];
       switch (i.op) {
           case '-':
           {
              box.remove_if([&](auto &&lens){ return lens.first == i.label; });
           }
           break;
           case '=':
           {
              auto pos = std::find_if(box.begin(), box.end(), [&] (auto && lens) { return lens.first == i.label; });
              if (pos != box.end()) {
                 pos->second = i.focal;
              } else {
                 box.emplace_back(std::make_pair(i.label, i.focal));
              }
           }
           break;
           default:
           throw "WTF";
       }
    }
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
        while (not input.empty()) {
            auto pos = input.find(',');
            data.emplace_back(input.substr(0, pos));
            if (pos != std::string::npos)
                input = input.substr(pos + 1);
            else
                input.clear();
        }
    }

    unsigned sum = 0;

    for (auto &l : data) {
       sum += hash(l);
    }

    std::cout << "Sum is: " << sum << '\n';


    auto instr = parse_instr(data);

    auto boxes = Boxes(256);

    run(boxes, instr);
    
    auto idx = 0;
    for (auto &b : boxes) {
       if (not b.empty())
           std::cout << "Box " << idx << ": " << to_string(b) << '\n';
       idx++;
    }

    auto focus_power = 0u;
    idx = 1;
    for (auto &box : boxes) {
       if (not box.empty())
       {
           auto lidx = 1;
           for (auto &[l, f] : box) {
               auto pow = idx * lidx * f;
               lidx++;
               focus_power += pow; 
           }
       }
       idx++;
    }
    
    std::cout << "Focus power is: " << focus_power << '\n';
}


