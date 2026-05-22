#include <vector>
#include <queue>
#include <utility>

class Solution
{
private:
    static constexpr int drs[] = {-1, 1, 0, 0};
    static constexpr int dcs[] = {0, 0, -1, 1};

    /**
     * Top down DP with memoization
     */
    static int max_inc_path_len_ending_at(const std::vector<std::vector<int>> &matrix,
                                          int r, int c, int m, int n,
                                          std::vector<std::vector<int>> &memo)
    {
        // If memo contains the answer, it means we have already computed it
        int &result = memo[r][c];
        if (result != -1)
            return result;

        // We can init the length of the longest increasing path that ending at
        // one of the neighbours as 0 and recursively call the function on the neighbours
        // and find the max
        int max_neighbour_len{0};
        for (int i = 0; i < 4; i++)
        {
            // Compute coordinates of the neighbour
            // If the neighbour is out of bounds we can skip it
            int new_r = r + drs[i];
            int new_c = c + dcs[i];
            if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                continue;

            // If the neighbour's value is >= the current cell's value then we can't append
            // the current cell's value to the increasing path ending at the neighbour
            // and increment the path's length by 1
            if (matrix[new_r][new_c] < matrix[r][c])
                max_neighbour_len = std::max(max_neighbour_len,
                                             max_inc_path_len_ending_at(matrix, new_r, new_c, m, n, memo));
        }

        // Add the max length of the increasing path ending among all its neighbours
        // (could be 0 if all neighbours are >= current cell's value) to 1
        // We can add the current cell to max neighbour's increasing path and increasing it by 1
        // Update the memo (result is a reference to memo[r][c]) and return the result
        result = 1 + max_neighbour_len;
        return result;
    }

    static int sol1(const std::vector<std::vector<int>> &matrix)
    {
        /**
         * * Explanation:
         * We form a directed graph with edges between adjacent cells (adjacent cells
         * aren't diagonal only vertically or horizontally adjacent) from a smaller
         * to a larger number.
         *
         * Lemma: This directed graph is a DAG
         * Proof:
         * Assume there exists a cycle u -> x1 -> x2 -> .. -> xn -> u
         * where n >= 1 as there are no self loops
         * We only have an edge u->v when v > u
         * so u < x1 < x2 < ... < xn < u => u < u => Contradiction
         * So there can't exist a cycle
         *
         * Since it is a DAG we can use DP to find the length of the longest path
         * (where we are defining the length of a path as the #vertices in the path
         * and not the #edges according to the leetcode problem)
         *
         * * DP Solution
         * dp[r][c]: The length of the longest increasing path ending at cell (r, c)
         * * Recurrence relation
         * dp[r][c] = 1 + max {dp[neighbour] if neighbour in bounds & matrix[neighbour] < matrix[r][c]}
         * Eg: If all neighbours in range are >= curren't cell's value then dp[r][c] = 1
         * as the longest path we can form ending at this cell is the path with this cell alone
         * * Base case
         * dp[src] = 1 if the cell is a source (all values around it are >= the cell's value)
         */

        // m = #rows and n = #columns in the grid
        // Create the memo
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));

        // Call the function on each cell to find the length of the longest
        // increasing path ending at that cell and keep tracking the maximum so far
        int max_path_len{0};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                max_path_len = std::max(max_path_len,
                                        max_inc_path_len_ending_at(matrix, r, c, m, n, memo));

        // Return the result
        return max_path_len;
    }

    /**
     * This is a lookahead version of the first solution
     * as we are calling this function with (r, c) only if memo[r][c] is -1
     * which means only if the value is not computed for (r, c)
     * We can lookup the solution for the neighbour (new_r, new_c) value in the memo if it
     * is already computed
     *
     * This would prevent the overhead of function calls for (r, c) values
     * for whom values are already computed
     */
    static void compute_max_path_len_ending_at(const std::vector<std::vector<int>> &matrix,
                                               int r, int c, int m, int n,
                                               std::vector<std::vector<int>> &memo)
    {
        // max_neighbour_len tracks the max increasing path length among all the neighbours
        // so it inits with 0
        int max_neighbour_len{0};
        for (int i = 0; i < 4; i++)
        {
            // If the neighbour is out of bounds we skip it
            int new_r = r + drs[i];
            int new_c = c + dcs[i];
            if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                continue;

            // If the neighbour's value is >= the current cell's value then we can't append
            // the current cell's value to the increasing path ending at the neighbour
            // and increment the path's length by 1
            if (matrix[new_r][new_c] < matrix[r][c])
            {
                // If the length of the max increasing path ending at the neighbour
                // isn't already computed we compute it
                if (memo[new_r][new_c] == -1)
                    compute_max_path_len_ending_at(matrix, new_r, new_c, m, n, memo);

                // We update the max so far among the neighbours
                max_neighbour_len = std::max(max_neighbour_len, memo[new_r][new_c]);
            }
        }

        // If this is a source, then its result is 1
        // So that is why we add 1 to the result of the max among all the neighbours
        // (which can be 0)
        memo[r][c] = 1 + max_neighbour_len;
    }

    /**
     * Lookahead version (instead of the base case version) of solution 1
     */
    static int sol2(const std::vector<std::vector<int>> &matrix)
    {
        // m = #rows and n = #columns in the grid
        // Create the memo
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));

        // Compute the length of the longest increasing path ending at each cell
        // and keep tracking the maximum so far
        int max_path_len{0};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
            {
                // If the max increasing path length ending at (r, c) is not computed
                // we compute it and compare it against the max so far
                if (memo[r][c] == -1)
                    compute_max_path_len_ending_at(matrix, r, c, m, n, memo);
                max_path_len = std::max(max_path_len, memo[r][c]);
            }

        // Return the result
        return max_path_len;
    }

    /**
     * BFS Version (Kahn's algorithm)
     */
    static int sol3(const std::vector<std::vector<int>> &matrix)
    {
        // m = #rows and n = #columns in the grid
        // Create the memo
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};

        // Create the queue and the 2d vector for indegrees
        std::queue<std::pair<int, int>> src_vertices;
        std::vector<std::vector<int>> in_degrees(m, std::vector<int>(n, 0));

        // Compute the indegrees of all the cells
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
            {
                int &in_degree = in_degrees[r][c];
                for (int i = 0; i < 4; ++i)
                {
                    // If neighbour is out of bounds we can skip it
                    int new_r = r + drs[i];
                    int new_c = c + dcs[i];
                    if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                        continue;

                    // If the neighbour's value < curr cell's value
                    // it means that there is an edge from the neighbour to the current cell
                    // so we can increment the indegree
                    if (matrix[new_r][new_c] < matrix[r][c])
                        in_degree++;
                }

                // If the indegree of the current cell is 0 then we add it to the queue
                if (!in_degree)
                    src_vertices.push({r, c});
            }

        // Run the BFS (Kahn's algorithm) as long as the queue is non-empty
        // In each iteration of the outer loop the invariant is that the
        // frontier solely consists of the source nodes (with 0 indegree) as we
        // remove a source node and decrement the indegrees of all its neighbours
        // and add the neighbour to the queue if its indegree becomes 0
        // We keep track of the distance layer by layer
        // We increment the number of bfs layers as we finish processing the nodes of each layer
        int num_bfs_layers{0};
        int num_src_vertices;
        while ((num_src_vertices = static_cast<int>(src_vertices.size())))
        {
            // Process each node (with indegree 0) of the frontier
            // 1. Remove it from the queue
            // 2. Decrement the indegree of all its neighbours
            // 3. If the neighbour's indegree becomes 0, we add it to the queue
            //   and it gets processed in the next iteration of the frontier
            for (int v = 0; v < num_src_vertices; v++)
            {
                // Remove a source node from the queue
                auto [r, c] = src_vertices.front();
                src_vertices.pop();

                // Decrement the indegree of all its neighbours
                for (int i = 0; i < 4; ++i)
                {
                    // Skip neighbours that are out of bounds
                    int new_r = r + drs[i];
                    int new_c = c + dcs[i];
                    if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n)
                        continue;

                    // Decrement the indegree of the neighbour and add it to the queue
                    // if its indegree becomes 0
                    if (matrix[new_r][new_c] > matrix[r][c])
                    {
                        in_degrees[new_r][new_c]--;
                        if (!in_degrees[new_r][new_c])
                            src_vertices.push({new_r, new_c});
                    }
                }
            }

            // Increment the number of layers as the layer is finished processing
            num_bfs_layers++;
        }

        // The number of layers at the end is the length of the longest path
        return num_bfs_layers;
    }

public:
    int longestIncreasingPath(std::vector<std::vector<int>> &matrix) { return sol3(matrix); }
};