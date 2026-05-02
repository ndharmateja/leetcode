#include <vector>
#include <queue>
#include <utility>

/**
 * Solving a similar problem on Neetcode as the original problem is a premium one.
 * Reference: https://neetcode.io/problems/islands-and-treasure/question
 */
class Solution
{
private:
    // All the land cells have this value
    inline static const int LAND = 2147483647;
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Multi source BFS solution
     * Theta(mn) time and Theta(V) space
     * where m = #rows, n = #cols, V = #verices
     *
     * See problem 994 for more details. Using a very similar idea.
     */
    static void solution1(std::vector<std::vector<int>> &grid)
    {
        // Run BFS with all the treasure cells as the source nodes
        // and explore the graph layer by layer and we'd get the shortest
        // distance to each reachable land cell from a treasure

        // Initialize data structures
        int num_rows{static_cast<int>(grid.size())}, num_cols{static_cast<int>(grid[0].size())};
        std::queue<std::pair<int, int>> queue;

        // Add all treasure cells (0) to the queue as the source nodes
        int r, c;
        for (r = 0; r < num_rows; r++)
            for (c = 0; c < num_cols; c++)
                if (!grid[r][c])
                    queue.push({r, c});

        // Main BFS Loop that runs layer by layer and updates the distances in the grid
        int curr_dist{1};
        while (!queue.empty())
        {
            // At this point the contents of the queue have one layer of elements
            // and we can process all of them using a for loop
            int num_elements_in_layer{static_cast<int>(queue.size())};

            for (int i = 0; i < num_elements_in_layer; i++)
            {
                // Pop the curr node
                auto [r, c] = queue.front();
                queue.pop();

                // Add all the unvisited neighbours to the queue
                // We know the neighbour is unvisited if the value is positive infinity
                // as we are marking the already visited nodes with the distance from a treasure
                // !Mark a cell visited as soon as we discover it to avoid adding same cells multiple times to the queue
                for (auto [dr, dc] : directions)
                {
                    int new_r{r + dr}, new_c{c + dc};

                    if ((0 <= new_r && new_r < num_rows) &&
                        (0 <= new_c && new_c < num_cols) &&
                        grid[new_r][new_c] == LAND)
                    {
                        // Update the distance of the neighbour (also acts as marking it as visited)
                        // and add it to the queue
                        grid[new_r][new_c] = curr_dist;
                        queue.push({new_r, new_c});
                    }
                }
            }

            // Increment the distance for the next layer
            curr_dist++;
        }
    }

    /**
     * Multi source BFS solution
     * Theta(mn) time and Theta(V) space
     * where m = #rows, n = #cols, V = #verices
     *
     * Exactly same idea as solution1 except we don't use a curr_dist variable
     */
    static void solution2(std::vector<std::vector<int>> &grid)
    {
        // Run BFS with all the treasure cells as the source nodes
        // and explore the graph layer by layer and we'd get the shortest
        // distance to each reachable land cell from a treasure

        // Initialize data structures
        int num_rows{static_cast<int>(grid.size())}, num_cols{static_cast<int>(grid[0].size())};
        std::queue<std::pair<int, int>> queue;

        // Add all treasure cells (0) to the queue as the source nodes
        int r, c;
        for (r = 0; r < num_rows; r++)
            for (c = 0; c < num_cols; c++)
                if (!grid[r][c])
                    queue.push({r, c});

        // Main BFS Loop that runs layer by layer and updates the distances in the grid
        // We can get the distance from the parent of a node in the BFS tree
        // and it works out well because the treasure's value is 0 which acts as the
        // distance of 0 of the source nodes
        // And we don't need a loop to go over graph layer by layer explicity
        // as we can directly get the distance
        while (!queue.empty())
        {
            // Pop the curr node
            auto [r, c] = queue.front();
            queue.pop();

            // Add all the unvisited neighbours to the queue
            // We know the neighbour is unvisited if the value is positive infinity
            // as we are marking the already visited nodes with the distance from a treasure
            // !Mark a cell visited as soon as we discover it to avoid adding same cells multiple times to the queue
            for (auto [dr, dc] : directions)
            {
                int new_r{r + dr}, new_c{c + dc};

                if ((0 <= new_r && new_r < num_rows) &&
                    (0 <= new_c && new_c < num_cols) &&
                    grid[new_r][new_c] == LAND)
                {
                    // Update the distance of the neighbour (also acts as marking it as visited)
                    // and add it to the queue
                    grid[new_r][new_c] = grid[r][c] + 1;
                    queue.push({new_r, new_c});
                }
            }
        }
    }

public:
    void islandsAndTreasure(std::vector<std::vector<int>> &grid) { return solution2(grid); }
};
