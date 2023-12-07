#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using Race = std::pair<unsigned, unsigned>;

using Data = std::vector<Race>;


unsigned count_victories(unsigned time, unsigned record) {
    unsigned count = 0;
    for (auto push = 1; push < time; push++) {
      if (push * (time - push) > record) {
          count++;
      }
    }
    return count;
}

int main() {

    auto data = Data{};

    auto times = std::string{};
    auto distances = std::string{};
    auto dummy = std::string{};

    getline(std::cin, times);
    getline(std::cin, distances);

    auto sst = std::stringstream{times};
    auto ssd = std::stringstream{distances};

    sst >> dummy;
    ssd >> dummy;

    auto t = unsigned{};
    auto d = unsigned{};
    while (ssd >> d && sst >> t) {
        data.emplace_back(std::make_pair(t, d));
    }


    unsigned mul = 1;
    for (const auto &[t, d] : data) {
        mul *= count_victories(t, d);
    }

    std::cout << "result is: " << mul << '\n';
}

