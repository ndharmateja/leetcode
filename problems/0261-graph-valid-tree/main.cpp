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
        return true;
    }

    bool are_connected(int p, int q) { return root(p) == root(q); }
    int get_num_sets() { return num_sets; }
};

/**
 * Solving a similar problem on Neetcode as the original problem is a premium one.
 * Reference: https://neetcode.io/problems/valid-tree/question
 */
class Solution
{
private:
    /**
     * Disjoint sets based solution
     */
    static bool solution1(int n, const std::vector<std::vector<int>> &edges)
    {
        // Base case
        // If the number of edges is not n-1 => not a tree
        if (edges.size() != n - 1)
            return false;

        // For the set of edges to be a tree, the graph has to be minimally connected
        // or maximally acyclic
        // We can use Disjoint sets to keep track of the connected components
        // and if at any point it forms a cycle => not acyclic => not a tree
        // and at the end if the number of components is not 1 => not connected => not a tree
        // otherwise it is a tree
        DisjointSets ds{n};

        // Process each edge
        for (const auto &edge : edges)
        {
            // If adding the edge (from, to) forms a cycle, return false
            // connect(from, to) will return false if from and to are already connected <=> a cycle
            int from = edge.front();
            int to = edge.back();
            if (!ds.connect(from, to))
                return false;
        }

        // At this point we can return true as there were n-1 edges exactly
        // and we don't have a cycle
        return true;
    }

    /**
     * TODO: DFS based solution to detect cycles and connectivity
     */
    static bool solution2(int n, const std::vector<std::vector<int>> &edges) {}

public:
    bool validTree(int n, const std::vector<std::vector<int>> &edges) { return solution1(n, edges); }
};
