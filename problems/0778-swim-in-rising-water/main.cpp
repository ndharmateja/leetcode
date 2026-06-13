#include <vector>
#include <iostream>

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

    bool are_connected(int p, int q) { return root(p) == root(q); }
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

    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    static int sol2(const std::vector<std::vector<int>> &grid)
    {
        int n{static_cast<int>(grid.size())};
        if (n == 1)
            return 0;
        int n_square{n * n};
        std::vector<std::pair<int, int>> reverse_lookup(n_square);
        int start{grid[0][0]}, end{grid[n - 1][n - 1]};

        // ! Buggy:
        // ! If start = 15 and end = 14, it returns 14 as the answer
        // ! if (end == n_square - 1 || end == n_square - 2)
        // !     return end;
        // ! if (start == n_square - 1 || start == n_square - 2)
        // !     return start;
        int max_start_end = std::max(start, end);
        if (max_start_end >= n_square - 2)
            return max_start_end;

        for (int r{0}; r < n; r++)
            for (int c{0}; c < n; c++)
                reverse_lookup[grid[r][c]] = {r, c};

        // Can start from 2 as even if start and end were 0 and 1
        // as the grid size is atleast 2x2, they can't directly connect
        DisjointSets ds{n_square};
        for (int t{2}; t < n_square; t++)
        {
            auto [r, c] = reverse_lookup[t];
            for (auto [dr, dc] : directions)
            {
                int new_r{r + dr}, new_c{c + dc};
                if (0 <= new_r && new_r < n &&
                    0 <= new_c && new_c < n &&
                    grid[new_r][new_c] < t)
                    ds.connect(t, grid[new_r][new_c]);
            }
            if (ds.are_connected(start, end))
                return t;
        }

        return -1;
    }

public:
    // Ideas:
    // 1. Disjoint sets solution
    // 2. BFS/DFS from the source and the destination
    // 3. BFS/DFS with paths maintaining a maxsofar (continue exploring even if
    //   smaller numbers are found - they won't be valid paths to those smaller number)
    //   But we continue exploring with a max so far to find paths to further numbers.
    //   A valid path to a cell (say has value x) is a path with every node along
    //   the path having a value <= x
    //   if we are able to find valid paths from the src and destination then we can easily
    //   the smallest node to which there are valid paths from both the src and destination
    // 4. Binary search + DFS/BFS to see if cells are connected using threshold on the
    //   cell value
    // 5. Dijkstra's modified
    int swimInWater(const std::vector<std::vector<int>> &grid) { return sol2(grid); }
};