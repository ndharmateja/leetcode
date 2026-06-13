#include <vector>
#include <utility>
#include <unordered_map>

class Node
{
public:
    int val;
    std::vector<Node *> neighbors;
    Node() : val{0}, neighbors{} {}
    Node(int _val) : val{_val}, neighbors{} {}
    Node(int _val, std::vector<Node *> _neighbors) : val{_val}, neighbors{std::move(_neighbors)} {}
};

class Solution
{
private:
    /**
     * Clones the graph node (recursively memoized) and all its reachable nodes
     * and returns the cloned counterpart of the node
     */
    static Node *dfs_and_clone(Node *node, std::unordered_map<Node *, Node *> &map)
    {
        // If the corresponding node already exists in the map, we can return it
        auto [it, inserted] = map.try_emplace(node, nullptr);
        if (!inserted)
            return it->second;

        // Otherwise we can create a new node corresponding to this node and insert
        // the corresponding node->cloned pair into the map
        Node *cloned = new Node(node->val);
        it->second = cloned;

        // Reserve the space for the neighbours of the cloned node
        // to prevent resizes of the vector
        cloned->neighbors.reserve(node->neighbors.size());

        // For each of the neighbours, clone the neighbour and add it as a neighbour
        // We have to add them in the same order of node's neighbours
        for (Node *neighbor : node->neighbors)
            cloned->neighbors.push_back(dfs_and_clone(neighbor, map));

        // Return the cloned node
        return cloned;
    }

    /**
     * Theta(V + E) time and Theta(V) space
     */
    static Node *sol1(Node *node)
    {
        // Base case
        if (!node)
            return nullptr;

        // General case
        std::unordered_map<Node *, Node *> map;
        return dfs_and_clone(node, map);
    }

public:
    Node *cloneGraph(Node *node) { return sol1(node); }
};