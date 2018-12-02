
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

std::vector<char> removeGarbage(std::vector<char> stream) {
    switch (stream[0]) {
        case '>':
            return std::vector<char>(stream.begin() + 1, stream.end());

        case '!':
            return removeGarbage(std::vector<char>(stream.begin() + 2, stream.end()));

        default:
            return removeGarbage(std::vector<char>(stream.begin() + 1, stream.end()));
    }
}

size_t doTheJob(std::vector<char> stream, size_t score = 0) {
    switch (stream[0]) {
        case '{':
            return doTheJob(std::vector<char>(stream.begin() + 1, stream.end()), score + 1);

        case '}':
            return score + (stream.size() == 1 ? 0 : doTheJob(std::vector<char>(stream.begin() + 1, stream.end()), score - 1));

        case ',':
            return doTheJob(std::vector<char>(stream.begin() + 1, stream.end()), score);

        case '<':
            return doTheJob(removeGarbage(std::vector<char>(stream.begin() + 1, stream.end())), score);
    }
}


int main() {
    std::vector<char> stream;
    std::string data;
    std::cin >> data;
    stream = std::vector<char>(data.begin(), data.end());
    std::cout << doTheJob(stream);
}
