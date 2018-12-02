
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Data {
    std::string name;
    std::vector<std::string> children;
};

std::string findRoot(std::vector<Data> &treedata) {
    for (const auto &candidate : treedata) {
        bool found = false;
        for (const auto &d : treedata) {
            if (std::find(d.children.begin(), d.children.end(), candidate.name) != d.children.end()) {
                found = true;
                break;
            }
        }
        if (!found) {
            return candidate.name;
        }
    }
    return {};
}

int main() {
    std::vector<Data> treedata;
    for (std::string linestr; std::getline(std::cin, linestr);) {
        if (linestr.empty())
            break;
        std::string dummy;
        Data data;

        std::istringstream ss(linestr);

        ss >> data.name;
        ss >> dummy; // get trid of weight

        while (ss) {
            std::string word;
            if (data.children.empty())
                ss >> dummy; // remove '->'
            ss >> word;

            word.erase(std::remove(word.begin(), word.end(), ','), word.end()); // remove commas

            data.children.push_back(word);
        }
        if (!data.children.empty()) // remove leaves as they cannot be root
            treedata.push_back(data);
    }
    std::cout << findRoot(treedata) << std::endl;

}
