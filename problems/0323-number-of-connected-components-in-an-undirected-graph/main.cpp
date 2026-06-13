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

/**
 * Solving a similar problem on Neetcode as the original problem is a premium one.
 * Reference: https://neetcode.io/problems/count-connected-components/question
 */
class Solution
{
private:
    /**
     * Uses disjoint sets and keeps unioning the vertices of each edge
     * This works better as we are given an edge list instead of an adjacency list
     *
     * For DFS/BFS based solutions, see problem 200
     * We can build an adjacency list in Theta(V + E) from the edge list and use that too
     *
     * Theta(V + Elog*(V)) amortized running time and Theta(V) space
     */
    static int solution1(int n, const std::vector<std::vector<int>> &edges)
    {
        // Initialize the disjoint sets data structure
        DisjointSets ds(n);

        // For each edge do a union of vertices connected by the edge
        // We maintain the number of connected components in 'n' itself
        // Each time there is a union of two different components, we decrement 'n'
        // connect() will return true if the two elements were not already connected
        for (const auto &edge : edges)
            if (ds.connect(edge[0], edge[1]))
                n--;

        // Return the number of disjoint sets (connected components)
        return n;
    }

public:
    int countComponents(int n, const std::vector<std::vector<int>> &edges) { return solution1(n, edges); }
};
