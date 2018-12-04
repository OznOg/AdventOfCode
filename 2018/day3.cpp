
#include <array>
#include <regex>
#include <iostream>

struct Rectangle {
    size_t id, x, y, w, h;
};

using Fabric = std::array<size_t, 1000*1000>;

void put_one(Fabric &f, const Rectangle &r) {
   for (auto i = 0u; i < r.w; ++i) {
       for (auto j = 0u; j < r.h; ++j) {
           f[r.x + i + 1000 * (r.y + j)]++;
       }
   }
}

void put_claims(Fabric &f, const std::vector<Rectangle> &v) {
    for (auto &r : v) {
        put_one(f, r);
    }
}

size_t count_overlap(const Fabric &f) {
    size_t count = 0;
    for (auto &e : f)
      if (e >= 2)
          count++;
    return count;
}


bool check_one(const Fabric &f, const Rectangle &r) {
   for (auto i = 0u; i < r.w; ++i) {
       for (auto j = 0u; j < r.h; ++j) {
           if (f[r.x + i + 1000 * (r.y + j)] > 1)
               return false;
       }
   }
   return true;
}

size_t check(const Fabric &f, const std::vector<Rectangle> &v) {
    for (auto &r : v) {
        if (check_one(f, r))
            return r.id;;
    }
    throw "bug";
}

int main() {

    std::string int_regex = "[-+]?[0-9]*";
    std::string space(R"REGEX(\s+)REGEX");
#define CAPTURE(x) (std::string("(") + (x) + std::string(")"))
   
    auto regex = std::string("^#") + CAPTURE(int_regex) + space + "@" + space + CAPTURE(int_regex)
                 + "," + CAPTURE(int_regex) + ":" + space + CAPTURE(int_regex) + "x" + CAPTURE(int_regex) + "$";


// #1 @ 151,671: 11x15
    std::string input;
    std::vector<Rectangle> inputs;

    while (getline(std::cin, input)) {

        std::smatch matches;

        if (std::regex_search(input, matches, std::regex(regex))) {
            Rectangle r;
            r.id = std::stoul(matches[1].str());
            r.x = std::stoul(matches[2].str());
            r.y = std::stoul(matches[3].str());
            r.w = std::stoul(matches[4].str());
            r.h = std::stoul(matches[5].str());
            inputs.push_back(r);
        } else {
            std::cout << "Cannot parse" << input << std::endl;
        }
    }

    Fabric fabric = {};
    put_claims(fabric, inputs);

    std::cout << "overlaps " << count_overlap(fabric) << std::endl;
    std::cout << "no overlap id" << check(fabric, inputs) << std::endl;
}
