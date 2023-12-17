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

using Group = std::vector<unsigned>;
using Springs = std::pair<std::string, Group>;
using Data = std::vector<Springs>;

unsigned matches(const std::string &l, std::vector<unsigned> &group) {
    auto g = std::vector<unsigned>{};
    g.push_back(0);
    unsigned idx = 0;
    while (idx < l.size()) {
        if (l[idx] == '.') {
            if (g.back() != 0)
               if (g.back() != group[g.size() - 1])
                   return 0;
               else
                   g.push_back(0);
        } else {
            g.back()++;
        }
        idx++;
    }
    if (g.back() == 0)
      g.resize(g.size() - 1);
    return g == group;
}

unsigned do_the_job(std::string &l, const std::vector<unsigned> &group, unsigned ref = 0, unsigned idx = 0,size_t pos = 0) {
    if (idx >= group.size()) {
       if (l.find('#', pos) != std::string::npos)
          return 0;
       return ref == 0;
    }

    if (pos == l.size()) {
        return (idx == group.size() && ref == 0) || idx == group.size() -1 && ref == group[idx];
    }
    
    if (l[pos] == '#') {
        ref++;
        if (ref > group[idx]) return 0;
        return do_the_job(l, group, ref, idx, pos + 1);
    }
    if (l[pos] == '.') {
        if (ref != 0) {
            if (ref != group[idx])
                return 0;
            idx++;
        }
        return do_the_job(l, group, 0, idx, pos + 1);
    }
   // if (l[pos] == '?') {
       // auto l2 = l;
        l[pos] = '#';
        auto c = do_the_job(l, group, ref, idx, pos);
        l[pos] = '.';
        c += do_the_job(l, group, ref, idx, pos);
        l[pos] = '?';
        return c;
    //}
    //throw "WTF";
}

bool match(const std::string &ref, const std::string &test, unsigned len_to_test) {
   for (int i = 0u; i < len_to_test; i++) {
      if (ref[i] != '?' && ref[i] != test[i])
         return false;
   }
   return true;
}

static uint64_t do_the_job2(const std::string &ref, std::string &l, const std::vector<unsigned> &group, unsigned _pos, unsigned idx, unsigned dol) noexcept {

    uint64_t sum = 0;
    for (unsigned d = 0; d < dol; d++) {
        auto pos = _pos;
    
        if (idx >= group.size())
           throw "WTF";

        if (group[idx] + d + pos > l.size())
           continue;
        for (unsigned i = 0; i < d; i++) {
            l[pos + i] = '.';
        }
        pos += d;
        for (unsigned i = 0; i < group[idx]; i++) {
            l[pos + i] = '#';
        }

        pos += group[idx];

        if (idx < group.size() - 1) {
            l[pos] = '.';
            pos += 1;
            if (match(ref, l, pos))
                sum += do_the_job2(ref, l, group, pos, idx + 1, dol - d);
        } else {
            for (unsigned i = pos; i < l.size(); i++) {
                l[i] = '.';
            }
            sum += match(ref, l, l.size());
        }
    }
    
    return sum;
}

unsigned deg_of_liberty(unsigned line_len, const Group &g) {
  auto min_size = 0;
  for (auto &v : g)
    min_size += v; 
  min_size += g.size() - 1; // add necessary spaces
  auto deg = line_len - min_size + 1;
  return deg;
}

auto force_pose(const std::string &s, const Group &group, unsigned degol) {
   std::string forced = s;

   auto pos = 0u;
   for (auto &v : group) {
      pos += v + 1;
      if (v > degol) {
         for (auto i = pos - degol; i < pos; i++) {
             forced[i] = '#';
         }
      }
   }
   return forced;
}

std::string to_string(const Group &group) {
   auto ss = std::stringstream{};
      ss << "[";
   for (auto &v: group) {
      ss << v << ',' ;
   }
      ss << "]";
   return ss.str();
}

int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
       auto groups_str = std::string{};
       Springs spring;
       auto ss = std::stringstream{input};
       ss >> spring.first >> groups_str; 

       while (not groups_str.empty()) {
          auto pos = groups_str.find(',');
          spring.second.push_back(std::stoi(groups_str.substr(0, pos)));
          if (pos != std::string::npos) { 
            pos++;
            groups_str = groups_str.substr(pos);
          } else groups_str.clear();
       }
       

       data.emplace_back(std::move(spring));
    }

   uint64_t sum = 0;
   #if 0
   for (auto &[l, g] : data) {
       auto count = do_the_job(l, g);
       sum += count;
   }
   #endif

   std::cout << "Sum is: " << sum << '\n';

   auto unfolded_data = data;
   for (auto &[l, g] : unfolded_data) {
       l = l + '?' + l + '?' + l + '?' + l + '?' + l;
       auto g2 = g;
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g2.insert(end(g2), begin(g), end(g));
       g = g2;
       if (g.empty())
          throw "WTF";
   }

   for (auto &[l, g] : unfolded_data) {
       auto dol = deg_of_liberty(l.size(), g);
       std::cout << "processing: " << l << " " << to_string(g) << " dol=" << dol << " " << std::flush;
     //  std::cout << "            " << force_pose(l, g, dol) << " degol " << dol << '\n';
       auto s = l;
       std::fill(s.begin(), s.end(), 'X');
       auto count = do_the_job2(l, s, g, 0, 0, dol);
       std::cout << " " << count << '\n';
       sum += count;
   }

   std::cout << "Sum is: " << sum << '\n';

}


