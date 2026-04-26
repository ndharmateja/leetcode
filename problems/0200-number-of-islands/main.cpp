#include <vector>
#include <utility>
#include <stack>
#include <functional>

class Solution
{
private:
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Recursive dfs function that explores all cells reachable from a given cell
     */
    static void dfs_recursive(std::vector<std::vector<char>> &grid, int i, int j, int num_rows, int num_cols)
    {
        // Mark this cell as visited
        grid[i][j] = '-';

        // Visit all unvisited neighbours that are 1s
        for (const auto &[dr, dc] : directions)
        {
            int r{i + dr}, c{j + dc};
            if ((0 <= r && r < num_rows) && (0 <= c && c < num_cols) && grid[r][c] == '1')
                dfs_recursive(grid, r, c, num_rows, num_cols);
        }
    }

    /**
     * Iterative dfs function that explores all cells reachable from a given cell
     */
    static void dfs_iterative(std::vector<std::vector<char>> &grid, int start_r, int start_c, int num_rows, int num_cols)
    {
        // Use a stack for dfs
        std::stack<std::pair<int, int>> stack;
        stack.push({start_r, start_c});

        // As long as the stack is empty
        while (!stack.empty())
        {
            // pop a cell and mark it as visited and add its unvisited neighbours
            // to the stack
            auto [r, c] = stack.top();
            stack.pop();

            // Visit all unvisited neighbours that are 1s
            for (const auto &[dr, dc] : directions)
            {
                int new_r{r + dr}, new_c{c + dc};
                if ((0 <= new_r && new_r < num_rows) && (0 <= new_c && new_c < num_cols) && grid[new_r][new_c] == '1')
                {
                    stack.push({new_r, new_c});

                    // We will push it and mark it as visited immediately so that we don't add
                    // duplicate cells to the stack
                    grid[new_r][new_c] = '-';
                }
            }
        }
    }

    /**
     * Like the explore function that calls dfs on each "island" on an unvisited
     * cell in that "island" and counts everytime dfs returns
     * We use the grid itself to keep track of the visited cells by making the char
     * '-' in that cell
     *
     * 'f' is the function that explores one island. eg: dfs/bfs etc
     */
    static int solution(std::vector<std::vector<char>> &grid, std::function<void(std::vector<std::vector<char>> &, int, int, int, int)> f)
    {
        int count{0}, num_rows{static_cast<int>(grid.size())}, num_cols{static_cast<int>(grid[0].size())};
        for (int i = 0; i < num_rows; i++)
            for (int j = 0; j < num_cols; j++)
            {
                // For each unvisited cell, we run dfs starting from that cell
                // so that the entire island gets explored and dfs marks all of the
                // vertices as visited and then we increase the count
                if (grid[i][j] == '1')
                {
                    f(grid, i, j, num_rows, num_cols);
                    count++;
                }
            }
        return count;
    }

    static int solution1(std::vector<std::vector<char>> &grid) { return solution(grid, dfs_recursive); }
    static int solution2(std::vector<std::vector<char>> &grid) { return solution(grid, dfs_iterative); }

public:
    int numIslands(std::vector<std::vector<char>> &grid) { return solution2(grid); }
};
