#include <vector>
#include <iostream>

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
    static int sol1(const std::vector<std::vector<int>> &grid)
    {
        int n{static_cast<int>(grid.size())};
        int src{grid[0][0]}, dest{grid[n - 1][n - 1]};
        int min_value{std::max(src, dest)}, max_value{n * n - 1};
        if (src == max_value || dest == max_value)
            return max_value;
        int min_so_far{max_value};
        while (min_value <= max_value)
        {
            int mid_value{min_value + (max_value - min_value) / 2};
            DisjointSets ds{mid_value + 1};
            for (int r = 0; r < n; r++)
                for (int c = 0; c < n - 1; c++)
                {
                    int curr = grid[r][c];
                    int right = grid[r][c + 1];
                    if (curr <= mid_value && right <= mid_value)
                        ds.connect(curr, right);
                }

            for (int c = 0; c < n; c++)
                for (int r = 0; r < n - 1; r++)
                {
                    int curr = grid[r][c];
                    int down = grid[r + 1][c];
                    if (curr <= mid_value && down <= mid_value)
                        ds.connect(curr, down);
                }

            if (ds.are_connected(src, dest))
            {
                min_so_far = mid_value;
                max_value = mid_value - 1;
            }
            else
                min_value = mid_value + 1;
        }
        return min_so_far;
    }

public:
    // Ideas:
    // 1. Disjoint sets solution
    // 2. BFS/DFS from the source and the destination
    int swimInWater(const std::vector<std::vector<int>> &grid) { return sol1(grid); }
};

int main()
{
    Solution s;
    s.swimInWater({{7, 23, 21, 9, 5},
                   {3, 20, 8, 18, 15},
                   {14, 13, 1, 0, 22},
                   {2, 10, 24, 17, 12},
                   {6, 16, 19, 4, 11}});
}