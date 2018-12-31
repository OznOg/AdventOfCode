
#include <array>
#include <regex>
#include <iostream>
#include <tuple>

struct Guard {
  size_t id;
  using Shift = std::pair<size_t, size_t>;
  std::vector<Shift> shifts;
  std::array<unsigned char, 60> cumulated;
};

size_t overal_sleep(const Guard &g) {
    size_t sum = 0;
    for (auto &c : g.cumulated) {
        sum += c;
    }
    return sum;
}

std::pair<size_t, size_t> max_sleep_minute(const Guard &g) {
    size_t max = 0;
    size_t minute = 0, max_minute = 0;
   
    for (auto &c : g.cumulated) {
        if (c > max) {
            max = c;
            max_minute = minute;
        }
        minute++;
    }
    return { max_minute, max };
}

int main() {

    std::string int_regex = "[-+]?[0-9]*";
    std::string space(R"REGEX(\s+)REGEX");
#define CAPTURE(x) (std::string("(") + (x) + std::string(")"))
   
    auto date = std::string("^\\[") + CAPTURE(int_regex) + "-"
                + CAPTURE(int_regex) + "-" 
                + CAPTURE(int_regex) + space 
                + CAPTURE(int_regex) + ":" 
                + CAPTURE(int_regex) + std::string("\\]");

// [1518-09-30 00:01] Guard #1549 begins shift
    auto guard = date + space + "Guard #" + CAPTURE(int_regex) + " begins shift$";
// [1518-11-19 00:01] falls asleep
    auto begin_sleep = date + space + "falls asleep$";
    auto end_sleep = date + space + "wakes up$";


    std::string input;
    std::map<size_t, Guard> guards;
    size_t curr_id;

    while (getline(std::cin, input)) {

        std::smatch matches;

        if (std::regex_search(input, matches, std::regex(guard))) {
            curr_id = std::stoul(matches[6].str());
            guards[curr_id].id = curr_id;
        } else if (std::regex_search(input, matches, std::regex(begin_sleep))) {
            auto &g = guards.at(curr_id);
            Guard::Shift s;
            s.first = std::stoul(matches[5].str());
            g.shifts.push_back(std::move(s));

        } else if (std::regex_search(input, matches, std::regex(end_sleep))) {
            auto &s = guards.at(curr_id).shifts.back();
            s.second = std::stoul(matches[5].str());
            auto &c = guards.at(curr_id).cumulated;
            for (auto i = s.first; i < s.second; ++i) {
                 c[i]++;
            }
        } else {
            std::cout << "Cannot parse" << input << std::endl;
        }
    }

#if 0
    for (auto &g : guards) {
        std::cout << "Guard " << g.second.id;
        #if 0
        for (auto &s : g.second.shifts) {
            std::cout << " sleep=" << s.first << " wakes=" << s.second;
        }
        std::cout << std::endl;
        #endif
        std::cout << " ";
        for (auto &c : g.second.cumulated) {
            if (c == 0)
                std::cout << ".";
            else
                std::cout << (char)('a' + c);
        }
        std::cout << std::endl;

    }
#endif
    size_t max_sleep_id = 0;
    size_t max_sleep = 0;
    for (auto &g : guards) {
          if (overal_sleep(g.second) > max_sleep) {
             max_sleep_id = g.first;
             max_sleep = overal_sleep(g.second);
          }
    }
    std::cout << "max id " << max_sleep_id << " max minute " << max_sleep_minute(guards[max_sleep_id]).first
              << " result is " << max_sleep_id * max_sleep_minute(guards[max_sleep_id]).first << std::endl;

    // part 2

    max_sleep_id = 0;
    max_sleep = 0;
    for (auto &g : guards) {
          if (max_sleep_minute(g.second).second > max_sleep) {
             max_sleep_id = g.first;
             max_sleep = max_sleep_minute(g.second).second;
          }
    }
    std::cout << "max id " << max_sleep_id << " max minute " << max_sleep_minute(guards[max_sleep_id]).first
              << " result is " << max_sleep_id * max_sleep_minute(guards[max_sleep_id]).first << std::endl;


}
