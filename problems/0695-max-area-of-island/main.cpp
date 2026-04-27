#include <vector>
#include <functional>
#include <algorithm>
#include <stack>
#include <utility>
#include <queue>

class Solution
{
private:
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Recursive dfs function that explores all cells reachable from a given cell
     * and counts the number of nodes in the connected component
     * Assumes that this function is called only on a unvisited cell
     */
    static int dfs_recursive(std::vector<std::vector<int>> &grid, int i, int j, int num_rows, int num_cols)
    {
        // Mark this cell as visited and count this cell
        grid[i][j] = -1;
        int count{1};

        // Visit all unvisited neighbours that are 1s
        for (const auto &[dr, dc] : directions)
        {
            int r{i + dr}, c{j + dc};
            if ((0 <= r && r < num_rows) && (0 <= c && c < num_cols) && grid[r][c] == 1)
                count += dfs_recursive(grid, r, c, num_rows, num_cols);
        }

        // Return the count
        return count;
    }

    /**
     * Iterative dfs function that explores all cells reachable from a given cell
     * and counts the number of nodes in the connected component
     */
    static int dfs_iterative(std::vector<std::vector<int>> &grid, int start_r, int start_c, int num_rows, int num_cols)
    {
        // Use a stack for dfs
        std::stack<std::pair<int, int>> stack;
        int count{0};

        // Add the start cell to the stack and mark it as visited
        stack.push({start_r, start_c});
        grid[start_r][start_c] = -1;

        // As long as the stack is empty
        while (!stack.empty())
        {
            // pop a cell and mark it as visited and add its unvisited neighbours
            // to the stack
            // Since we are adding every node to the stack only once and every element
            // is added, we can increment the count of number of nodes in the connected component
            // once we pop a node from the stack
            auto [r, c] = stack.top();
            stack.pop();
            count++;

            // Visit all unvisited neighbours that are 1s
            for (const auto &[dr, dc] : directions)
            {
                int new_r{r + dr}, new_c{c + dc};
                if ((0 <= new_r && new_r < num_rows) && (0 <= new_c && new_c < num_cols) && grid[new_r][new_c] == 1)
                {
                    // We will push it and mark it as visited immediately so that we don't add
                    // duplicate cells to the stack
                    stack.push({new_r, new_c});
                    grid[new_r][new_c] = -1;
                }
            }
        }

        // Return the number of nodes in the connected component
        return count;
    }

    /**
     * BFS function that explores all cells reachable from a given cell
     * and counts the number of nodes in the connected component
     */
    static int bfs(std::vector<std::vector<int>> &grid, int start_r, int start_c, int num_rows, int num_cols)
    {
        // Use a queue for dfs
        std::queue<std::pair<int, int>> queue;
        int count{0};

        // Add the start cell to the queue and mark it as visited
        queue.push({start_r, start_c});
        grid[start_r][start_c] = -1;

        // As long as the queue is empty
        while (!queue.empty())
        {
            // pop a cell and mark it as visited and add its unvisited neighbours
            // to the queue
            // Since we are adding every node to the queue only once and every element
            // is added, we can increment the count of number of nodes in the connected component
            // once we pop a node from the queue
            auto [r, c] = queue.front();
            queue.pop();
            count++;

            // Visit all unvisited neighbours that are 1s
            for (const auto &[dr, dc] : directions)
            {
                int new_r{r + dr}, new_c{c + dc};
                if ((0 <= new_r && new_r < num_rows) && (0 <= new_c && new_c < num_cols) && grid[new_r][new_c] == 1)
                {
                    // We will push it and mark it as visited immediately so that we don't add
                    // duplicate cells to the queue
                    queue.push({new_r, new_c});
                    grid[new_r][new_c] = -1;
                }
            }
        }

        // Return the number of nodes in the connected component
        return count;
    }

    /**
     * Like the explore function that calls dfs on each "island" on an unvisited
     * cell in that "island" and counts the number of nodes in each connected component
     * We use the grid itself to keep track of the visited cells by making the value
     * -1 in that cell
     *
     * 'f' is the function that explores one island. eg: dfs/bfs etc
     */
    static int solution(std::vector<std::vector<int>> &grid, std::function<int(std::vector<std::vector<int>> &, int, int, int, int)> f)
    {
        int max_nodes{0}, num_rows{static_cast<int>(grid.size())}, num_cols{static_cast<int>(grid[0].size())};
        for (int i = 0; i < num_rows; i++)
            for (int j = 0; j < num_cols; j++)
            {
                // For each unvisited cell, we run dfs starting from that cell
                // so that the entire island gets explored and dfs counts the number of nodes
                // in that connected component
                if (grid[i][j] == 1)
                    max_nodes = std::max(max_nodes, f(grid, i, j, num_rows, num_cols));
            }
        return max_nodes;
    }

    static int solution1(std::vector<std::vector<int>> &grid) { return solution(grid, dfs_iterative); }
    static int solution2(std::vector<std::vector<int>> &grid) { return solution(grid, dfs_recursive); }
    static int solution3(std::vector<std::vector<int>> &grid) { return solution(grid, bfs); }

public:
    int maxAreaOfIsland(std::vector<std::vector<int>> &grid) { return solution1(grid); }
};