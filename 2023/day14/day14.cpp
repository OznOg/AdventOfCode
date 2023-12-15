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

using Line = std::string;
using Data = std::vector<Line>;

std::string stringify(const Data &d){
    std::string s;
    for (auto &l : d)
      s += l;
    return s;
}

Data rotateKW(const Data &data) {
   auto rotated = Data(data.front().size());
   for (auto &l : rotated) {
      l.resize(data.size());
   }

   for (auto j = 0u; j < data.size(); j++) {
       for (auto i = 0u; i < data.front().size(); i++) {
          rotated[i][rotated.size() - 1 - j] = data[j][i]; 
       }
   }
   return rotated; 
}

Data rotateAKW(const Data &data) {
   auto rotated = Data(data.front().size());
   for (auto &l : rotated) {
      l.resize(data.size());
   }

   for (auto j = 0u; j < data.size(); j++) {
       for (auto i = 0u; i < data.front().size(); i++) {
          rotated[rotated.size() - 1 - i][j] = data[j][i]; 
       }
   }
   return rotated; 
}

Data tilt(const Data &data) {
    auto tilted = Data(data.size());

    for (auto j = 0u; j < data.size(); j++) {
        for (auto i = 0u; i < data[j].size(); i++) {
           auto &l = data[j];
           if (l[i] == 'O')
              tilted[j].append(1, 'O');
           else if (l[i] == '#') {
              for (auto k = tilted[j].size(); k < i; k++) {
                  tilted[j].append(1, '.');
              }
              tilted[j].append(1, '#');
           }
              
        }
        tilted[j].append(data[j].size() - tilted[j].size(), '.');
    }
    return tilted;
}

static inline Data cycle(const Data &data) {
    auto rotated = rotateKW(data); // N
    rotated = tilt(rotated); //N
    rotated = rotateKW(rotated); // W
    rotated = tilt(rotated); //W
    rotated = rotateKW(rotated); // S
    rotated = tilt(rotated); //S
    rotated = rotateKW(rotated); // E
    rotated = tilt(rotated); //E
    return rotated;
}


unsigned compute(Data data) {
    data = rotateKW(data); // N
    //data = rotateKW(data); // N
    //data = rotateKW(data); // N
    //data = tilt(data); //N
    auto sum = 0;
    for (auto &l : data) {
       for (auto i = 0u; i < l.size(); i++) {
           if (l[i] == 'O') {
              sum += l.size() - i;
           }
       }
    }
   return sum;
}
int main() {

    auto data = Data{};

    auto input = std::string{};
    while (getline(std::cin, input)) {
        data.emplace_back(input);
    }


    auto transposed = rotateAKW(data);
    auto tilted = tilt(transposed);

    auto sum = 0;
    for (auto &l : tilted) {
       for (auto i = 0u; i < l.size(); i++) {
           if (l[i] == 'O') {
              sum += l.size() - i;
           }
       }
    }

    std::cout << "Sum is: " << sum << '\n';
    
    auto rotated = rotateKW(tilted); //W
    rotated = tilt(rotated); //W
    rotated = rotateKW(rotated); // S
    rotated = tilt(rotated); //S
    rotated = rotateKW(rotated); // E
    rotated = tilt(rotated); //E
    
    auto ref = std::vector<std::string>{};
    
    auto size = ref.size() + 1;
    auto count = 1;
     while (size != ref.size()) 
     {
         size = ref.size();

         rotated = cycle(rotated);

         auto s = stringify(rotated);
         if (std::find(ref.begin(), ref.end(), s) == ref.end())
             ref.emplace_back(std::move(s));
         count += 1;
         std::cout << "count => " << compute(rotated) << '\n';
     }
     //for (auto s:ref) {
     //    std::cout <<  s << '\n';
     //}
     //std::cout << (stringify(rotated)) << '\n';
     {
         auto s = stringify(rotated);
         auto dist = std::find(ref.begin(), ref.end(), s) - ref.begin();
         auto pattern_size = ref.size() - dist; 
         auto remaining = 1'000'000'000ull - count;
         remaining %= pattern_size;
         for (auto i = 0; i < remaining; i++) {
             rotated = cycle(rotated);
         }
     }
     #if 0
    {
    rotated = rotateKW(rotated); // N
    rotated = tilt(rotated); //N
    rotated = rotateKW(rotated); // W
    rotated = tilt(rotated); //W
    rotated = rotateKW(rotated); // S
    rotated = tilt(rotated); //S
    rotated = rotateKW(rotated); // E
    rotated = tilt(rotated); //E
    }
    #endif

    rotated = rotateKW(rotated); // N
    //rotated = tilt(rotated); //N
    sum = 0;
    for (auto &l : rotated) {
       for (auto i = 0u; i < l.size(); i++) {
           if (l[i] == 'O') {
              sum += l.size() - i;
           }
       }
    }

    { // put back in good referencial
    //rotated = rotateKW(rotated); 
    rotated = rotateKW(rotated);
    }
    for (auto &l : rotated)
        std::cout << l << '\n';
    

    std::cout << count << '\n';

    std::cout << "Sum #2 is: " << sum << '\n';
}


