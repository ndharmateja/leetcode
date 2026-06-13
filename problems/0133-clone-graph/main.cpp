#include <vector>
#include <queue>
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

    /**
     * Clones the graph node using BFS
     *
     * Theta(V + E) time and Theta(V) space
     */
    static Node *sol2(Node *node)
    {
        // Base case
        if (!node)
            return nullptr;

        // Invariants:
        // 1. The nodes added to the queue have already been cloned and in the map
        // 2. The neighbours of the nodes in the queue are empty

        // Create the clone of node and add the node to the queue to start BFS
        Node *node_clone = new Node(node->val);
        std::unordered_map<Node *, Node *> map;
        map[node] = node_clone;
        std::queue<Node *> queue;
        queue.push(node);

        // BFS main loop
        while (!queue.empty())
        {
            // Dequeue the node and clone & add its neighbours as the
            // neighbours of the cloned node
            Node *curr = queue.front();
            queue.pop();

            // Get the corresponding cloned node (exists in the map as per the invariant)
            Node *curr_clone = map[curr];
            curr_clone->neighbors.reserve(curr->neighbors.size());

            // For each of the neighbours, if it was already cloned
            // we can get it from the map and add it as the neighbour of curr_clone
            // Otherwise we can create the clone and add it to the queue
            for (Node *neighbor : curr->neighbors)
            {
                // If the neighbour wasn't already cloned, we clone it and add it to the map
                // and push it to the queue as we cloned it for the first time
                auto [it, inserted] = map.try_emplace(neighbor, nullptr);
                if (inserted)
                {
                    it->second = new Node(neighbor->val);
                    queue.push(neighbor);
                }

                // Add the cloned neighbour as the neighbour of curr_clone
                curr_clone->neighbors.push_back(it->second);
            }
        }

        // Return the clone of the given node
        return node_clone;
    }

    /**
     * Clones the graph node using BFS
     * Same as solution 2 except we use a vector instead of an unordered_map
     * to leverage the leetcode constraints:
     * 1. The number of nodes in the graph is in the range [0, 100].
     * 2. 1 <= node.val <= 100
     * 3. node.val is unique for each node.
     * So we can use a vector of size 101 instead of the unordered_map to speed up lookups
     *
     * Theta(V + E) time and Theta(V) space
     */
    static Node *sol3(Node *node)
    {
        // Base case
        if (!node)
            return nullptr;

        // Invariants:
        // 1. The nodes added to the queue have already been cloned and in the map
        // 2. The neighbours of the nodes in the queue are empty

        // Create the clone of node and add the node to the queue to start BFS
        Node *node_clone = new Node(node->val);
        std::vector<Node *> map(101, nullptr);
        map[node->val] = node_clone;
        std::queue<Node *> queue;
        queue.push(node);

        // BFS main loop
        while (!queue.empty())
        {
            // Dequeue the node and clone & add its neighbours as the
            // neighbours of the cloned node
            Node *curr = queue.front();
            queue.pop();

            // Get the corresponding cloned node (exists in the map as per the invariant)
            Node *curr_clone = map[curr->val];
            curr_clone->neighbors.reserve(curr->neighbors.size());

            // For each of the neighbours, if it was already cloned
            // we can get it from the map and add it as the neighbour of curr_clone
            // Otherwise we can create the clone and add it to the queue
            for (Node *neighbor : curr->neighbors)
            {
                // If the neighbour wasn't already cloned, we clone it and add it to the map
                // and push it to the queue as we cloned it for the first time
                // ! We create a reference to prevent frequent indexing into the vector
                Node *&neighbor_clone = map[neighbor->val];
                if (!neighbor_clone)
                {
                    neighbor_clone = new Node(neighbor->val);
                    queue.push(neighbor);
                }

                // Add the cloned neighbour as the neighbour of curr_clone
                curr_clone->neighbors.push_back(neighbor_clone);
            }
        }

        // Return the clone of the given node
        return node_clone;
    }

public:
    Node *cloneGraph(Node *node) { return sol2(node); }
};