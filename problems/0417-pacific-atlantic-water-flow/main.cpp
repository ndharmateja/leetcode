#include <vector>
#include <deque>
#include <utility>

/**
 * 1. vector<vector<bool>> better than set<pair<int, int>> to store the result/visited
 * of the BFS as vector<bool> takes 1 bit per cell and the running time to insert
 * won't be log n and cache locality is much better
 * 2. vector<bool> would be even better where each index i is the row major index of (r, c)
 *    a. 2 lookups or visited[r][c] vs 1 lookup visited[r * num_cols + c]
 *    b. memory overhead of vector of vectors vs one flattened vector
 * 3. unordered_set<int> could also be used for the visited/result
 * but vector<bool> would have much better cache locality and lookup speed
 * 4. Idea: Pass a function to BFS that does nothing while running BFS on the pacific ocean part
 * but while running the atlantic ocean part, can see if the cell can reach pacific and directly
 * add it to the result instead of having to do the loop at the end
 */

class Solution
{
private:
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Multi source BFS solution
     * Runs BFS using the elements in the @param queue as the source nodes
     * and populates the @param visited with all the nodes that are reachable from
     * the source nodes in the reverse graph
     */
    static void bfs(const std::vector<std::vector<int>> &heights,
                    std::deque<std::pair<int, int>> &queue,
                    std::vector<bool> &visited,
                    int num_rows, int num_cols)
    {
        // We can use the result set as a visited set
        // So we can initially mark all the source nodes as visited
        for (auto [r, c] : queue)
            visited[r * num_cols + c] = true;

        // BFS main loop
        while (!queue.empty())
        {
            auto [r, c] = queue.front();
            queue.pop_front();

            // Add all the neighbours of curr in the reverse graph that aren't
            // visited already
            // The way we check if there is an edge from (r, c) -> (new_r, new_c)
            // in the *reverse graph* is if the heights[r][c] <= heights[new_r][new_c]
            // as in the original graph there is an edge from (r, c) -> (r', c') if h[r][c] >= h[r'][c']
            // !Mark a cell visited as soon as we discover it to avoid adding same cells multiple times to the queue
            for (auto [dr, dc] : directions)
            {
                int new_r = r + dr;
                int new_c = c + dc;
                int new_index = new_r * num_cols + new_c;
                if ((0 <= new_r && new_r < num_rows) &&
                    (0 <= new_c && new_c < num_cols) &&
                    (heights[r][c] <= heights[new_r][new_c]) &&
                    !visited[new_index])
                {
                    queue.push_back({new_r, new_c});
                    visited[new_index] = true;
                }
            }
        }
    }

    /**
     * Theta(mn) time and Theta(mn) space
     * where m = #rows and n = #cols
     */
    static std::vector<std::vector<int>> solution1(const std::vector<std::vector<int>> &heights)
    {
        // Run BFS on the reverse graph with all the pacific ocean border nodes
        // to figure out all the cells that can reach the pacific ocean
        // Do the same for the atlantic ocean
        // The common nodes between them are the ones that can reach both the pacific and the
        // atlantic ocean

        // We are representing the cell by row major indices
        // index i for cell (r, c) = r * num_cols + c

        // Create the queue with the source nodes as the pacific ocean border nodes
        // which are all then nodes on the left and top sides
        int num_rows{static_cast<int>(heights.size())}, num_cols{static_cast<int>(heights[0].size())};

        // We are using a queue so that we can iterate over its elements inside
        // the BFS function
        std::deque<std::pair<int, int>> queue;

        // Add all the cells of the first row and the first col
        queue.push_back({0, 0});
        for (int c = 1; c < num_cols; c++)
            queue.push_back({0, c});
        for (int r = 1; r < num_rows; r++)
            queue.push_back({r, 0});

        // Run BFS on the reverse graph with the pacific ocean border nodes
        // to find all the nodes that can reach pacific ocean
        std::vector<bool> can_reach_pacific(num_rows * num_cols, false);
        bfs(heights, queue, can_reach_pacific, num_rows, num_cols);

        // Do the same for atlantic ocean
        // Queue is empty at this point as we run BFS until the queue is empty
        // Add all the cells of the last row and the last col
        queue.push_back({num_rows - 1, num_cols - 1});
        for (int c = 0; c < num_cols - 1; c++)
            queue.push_back({num_rows - 1, c});
        for (int r = 0; r < num_rows - 1; r++)
            queue.push_back({r, num_cols - 1});

        // Run BFS on the reverse graph with the atlantic ocean border nodes
        // to find all the nodes that can reach atlantic ocean
        std::vector<bool> can_reach_atlantic(num_rows * num_cols, false);
        bfs(heights, queue, can_reach_atlantic, num_rows, num_cols);

        // At this point we need the common nodes between the set of nodes that
        // can reach pacific and also atlantic
        std::vector<std::vector<int>> result;
        int row_major_index{0};
        for (int r = 0; r < num_rows; r++)
            for (int c = 0; c < num_cols; c++)
            {
                if (can_reach_pacific[row_major_index] && can_reach_atlantic[row_major_index])
                    result.push_back({r, c});
                row_major_index++;
            }

        // Return the result
        return result;
    }

public:
    std::vector<std::vector<int>> pacificAtlantic(const std::vector<std::vector<int>> &heights) { return solution1(heights); }
};