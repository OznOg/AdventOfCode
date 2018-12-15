

#include <iostream>
#include <vector>

struct Node {
    std::vector<Node> children;
    std::vector<int> metadata;
};

Node readNode() {
    Node node;
    size_t child_count, md_count;
    std::cin >> child_count >> md_count;
    for (auto i = 0u; i < child_count; i++) {
        node.children.emplace_back(readNode());
    }
    for (auto i = 0u; i < md_count; i++) {
        size_t md;
        std::cin >> md;
        node.metadata.push_back(md);
    }
    return node;
}

size_t sum(const Node &n) {
    size_t s = 0;
    for (auto &md : n.metadata)
        s += md;

    for (auto &c : n.children)
        s += sum(c);

    return s;
}

size_t sum2(const Node &n) {
    size_t s = 0;
   
    if (n.children.empty())
        return sum(n);

    for (auto &md : n.metadata)
        if (md <= n.children.size())
            s += (md == 0 ? 0 : sum2(n.children[md - 1]));

    return s;
}

int main() {
    Node root = readNode();
    std::cout << "Part1: " << sum(root) << std::endl;
    std::cout << "Part2: " << sum2(root) << std::endl;
}

