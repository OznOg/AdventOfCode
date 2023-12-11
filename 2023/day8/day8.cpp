#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <optional>


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
    std::vector<std::string> all_sequences;
    std::optional<size_t> repeat_idx;
    std::vector<size_t> z_positions;
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
                n.sequence.append(n.node->label);
                if (n.node->end_with_z) n.z_positions.push_back(step);
                if (instructions[step % instructions.size()] == 'R')
                    n.node = n.node->right;
                else
                    n.node = n.node->left;
            }
            step++;
            if (step % instructions.size() == 0) {
                finished = true;
                for (auto &n : next) {
                    auto it = std::find(n.all_sequences.begin(),
                              n.all_sequences.end(),
                              n.sequence);
                    if (it == n.all_sequences.end()) {
                        finished = false;
                        n.all_sequences.emplace_back(std::move(n.sequence));
                    } else {
                       if (not n.repeat_idx) {
                           n.repeat_idx = it -  n.all_sequences.begin();
                       }
                       n.sequence.clear();
                    }
                }
            }
        }
        size_t idx = 0;
        for (auto &n : next) {
            std::cout << "Idx: " << idx << " sequence is: " << n.all_sequences.size() - 1 << " idx: " << n.repeat_idx.value()
                      << " size: " << (n.all_sequences.size() - n.repeat_idx.value()) * instructions.size()
                      << " z-positions: " << n.z_positions.front() % (n.all_sequences.size() - 1) << '(' << n.z_positions.size() << ')' << '\n';
            idx++;
        }
         
        //for (auto &s : next[2].all_sequences) {
        //    std::cout << s << '\n';
        //}

        std::vector<std::pair<unsigned, unsigned>> gna = {
            {53, 1},
            {73, 1 },
            {47, 1},
            {61, 1},
            {71, 1},
            {59, 1}
        };

#if 0
        auto all_zero = [&gna] {
          for (auto &[t, c] : gna) {
              if (c % t != 0)
                  return false;
          }
          return true;
        };

        auto coucount = 1u;
        while (not all_zero()) {
          for (auto &[t, c] : gna) {
              c += 73;
          }
          coucount++;
        }
        std::cout << coucount << '\n';
        #endif

        //for (auto &s : next[1].all_sequences) {
        //    std::cout << s << '\n';
        //}

          
    }

            std::cout << "instructions: " << instructions.size() << '\n';
            std::cout << 307ul * 46466159947ul << '\n';

    // Il faut ppcm pout revenir a la meme position

}

