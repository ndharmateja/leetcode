#include <vector>

class DisjointSets
{
private:
    int num_sets;
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
    DisjointSets(int n) : num_sets{n}, size(n, 1)
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

    // Weighted quick union
    void connect(int p, int q)
    {
        // Get the roots of each of the trees
        int p_root = root(p);
        int q_root = root(q);

        // If both of them belong to the same tree, they are already connected
        if (p_root == q_root)
            return;

        // Decrement the number of sets by 1 as we are merging two sets
        num_sets--;

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
    }

    bool are_connected(int p, int q) { return root(p) == root(q); }
    int get_num_sets() { return num_sets; }
};

class Solution
{
private:
    /**
     * Uses disjoint sets and keeps unioning the vertices of each edge
     * This works better as we are given an edge list instead of an adjacency list
     *
     * For DFS/BFS based solutions, see problem 200
     * We can build an adjacency list in Theta(V + E) from the edge list and use that too
     */
    static int solution1(int n, const std::vector<std::vector<int>> &edges)
    {
        // Initialize the disjoint sets data structure
        DisjointSets ds(n);

        // For each edge do a union of vertices connected by the edge
        // We could have had a num_components variable here too, decrementing each time
        // there is a successful union between two connected components
        for (const auto &edge : edges)
            ds.connect(edge[0], edge[1]);

        // Return the number of disjoint sets (connected components)
        return ds.get_num_sets();
    }

public:
    int countComponents(int n, const std::vector<std::vector<int>> &edges) { return solution1(n, edges); }
};
