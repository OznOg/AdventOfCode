#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>


using NodeList = std::map<std::string, std::pair<std::string, std::string>>;

using Data = std::pair<std::string, NodeList>;


struct Node {
    std::string label;
    bool end_with_z;
    Node *left;
    Node *right;
};

struct Sequence {
    const Node *node;
    std::string sequence;
    std::set<std::string> all_sequences;
};


std::map<std::string, Node> makeNodes(NodeList &nodelist) {
    auto nodes = std::map<std::string, Node>{};

    // create all nodes
    for (auto &[label, dir] : nodelist) {
        nodes[label] = Node{label, label.back() == 'Z', nullptr,  nullptr};
    }

    // bind them
    for (auto &[label, dir] : nodelist) {
       auto &node = nodes[label];
       node.left = &nodes[dir.first];
       node.right = &nodes[dir.second];
    }
    return nodes;
}


int main() {

    auto data = Data{};

    getline(std::cin, data.first);


    auto input = std::string{};
    getline(std::cin, input); // drop empty line

    while (getline(std::cin, input)) {
       auto label = input.substr(0, 3);;
       auto left = input.substr(7, 3);;
       auto right = input.substr(12, 3);;

       data.second[label] = std::make_pair(left, right);
    }

    auto &[instructions, network] = data;

#if 0
    {
        auto step = 0u;
        auto next = std::string{"AAA"};
        while (next != "ZZZ") {
            auto &[left, right] = network[next];
            if (instructions[step % instructions.size()] == 'R')
               next = right;
            else
               next = left;
            step++;
        }
        std::cout << "Steps are is: " << step << '\n';
    }
    #endif

    #if 0
    {
        auto step = 0u;
        auto next = std::vector<const std::string *>{};
       
        for (const auto &[label, dir] : network) {
            if (label.back() == 'A')
                next.push_back(&label);
        }


        auto all_end_with_Z = [] (const std::vector<const std::string *> &v) {
            return std::all_of(v.begin(), v.end(), [](auto &e) { return e->back() == 'Z';});
        };

        while (not all_end_with_Z(next)) {
            for (auto &n : next) {
                auto &[left, right] = network[*n];
                if (instructions[step % instructions.size()] == 'R')
                    n = &right;
                else
                    n = &left;
            }
            step++;
        }
        std::cout << "Steps are is: " << step << '\n';
    }
    #endif

    {
        auto step = 0lu;
        auto nodes = makeNodes(network);
        auto next = std::vector<Sequence>{};
       
        for (auto &[label, node] : nodes) {
            if (label.back() == 'A') {
                next.push_back({&node, {}, {}});
            }
        }
        auto all_end_with_Z = [] (const std::vector<const Node *> &v) {
            return std::all_of(v.begin(), v.end(), [](auto &n) { return n->end_with_z;});
        };

        std::string sequence;
        std::set<std::string> all_sequences;
        bool finished = false;
        while (not finished) {
            for (auto &n : next) {
                n.sequence += n.node->label;
                if (instructions[step % instructions.size()] == 'R')
                    n.node = n.node->right;
                else
                    n.node = n.node->left;
            }
            step++;
            if (step % instructions.size() == 0) {
                finished = true;
                for (auto &n : next) {
                    if (not n.all_sequences.contains(n.sequence))
                        finished = false;
                    n.all_sequences.insert(std::move(n.sequence));
                }
            }
        }
        size_t idx = 0;
        for (auto &n : next) {
            std::cout << "Idx: " << idx << " sequence is: " << n.all_sequences.size() << '\n';
            idx++;
        }
    }

}

