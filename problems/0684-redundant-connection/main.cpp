#include <vector>

class DisjointSets
{
private:
    std::vector<int> parent;
    std::vector<int> size;

    // Path compression
    int root(int p)
    {
        if (p != parent[p])
            parent[p] = root(parent[p]);
        return parent[p];
    }

public:
    // Initially all elements in size will just be 1
    DisjointSets(int n) : size(n, 1)
    {
        // Initialize the n components as initially all disconnected
        // Each element will have itself as its own parent
        // We are using reserve so that we don't have to init the array with 0s
        // instead it will just reserve space so that we don't have to keep
        // resizing the dynamic array
        parent.reserve(n);
        for (int i = 0; i < n; i++)
            parent.push_back(i);
    }

    /**
     * Weighted quick union
     * @return true if the two elements were not already connected, false otherwise
     */
    bool connect(int p, int q)
    {
        // Get the roots of each of the trees
        int p_root = root(p);
        int q_root = root(q);

        // If both of them belong to the same tree, they are already connected
        if (p_root == q_root)
            return false;

        // Attach the smaller size tree to the root of the larger size tree
        // and update the sizes
        if (size[p_root] < size[q_root])
        {
            parent[p_root] = q_root;
            size[q_root] += size[p_root];
        }
        else
        {
            parent[q_root] = p_root;
            size[p_root] += size[q_root];
        }
        return true;
    }
};

class Solution
{
private:
    /**
     * Disjoint sets based solution
     */
    static std::vector<int> solution1(const std::vector<std::vector<int>> &edges)
    {
        // For the set of edges to be a tree, the graph has to be minimally connected
        // or maximally acyclic
        // We can use Disjoint sets to keep track of the connected components
        // and if at any point an edge forms a cycle => that would be the last edge
        // (among the given edges) that is a redundant edge
        int n{static_cast<int>(edges.size())};
        DisjointSets ds{n};

        // Process each edge
        for (const auto &edge : edges)
        {
            // Check if adding a new edge forms a cycle
            // if yes, that edge can be removed to make the graph a tree
            // Edges are 1-indexed based, so we convert them into 0-indexed before adding to the
            // disjoint sets data structure
            int from = edge.front() - 1;
            int to = edge.back() - 1;
            if (!ds.connect(from, to))
                return edge;
        }

        // We would never reach here as it is guaranteed to have exactly n edges and n vertices
        // which are connected
        return {-1, -1};
    }

public:
    std::vector<int> findRedundantConnection(const std::vector<std::vector<int>> &edges) { return solution1(edges); }
};