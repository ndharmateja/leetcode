#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

class Solution
{
private:
    static inline const int POS_INF = std::numeric_limits<int>::max();

    /**
     * Finds the sum of x and y
     * This function is to prevent overflows when one of the operands is POS_INF
     *
     * Eg:
     * sum(2      , 3      ) = 5
     * sum(POS_INF, x      ) = POS_INF
     * sum(x      , POS_INF) = POS_INF
     * sum(POS_INF, POS_INF) = POS_INF
     */
    static inline int sum(int x, int y) { return (x == POS_INF || y == POS_INF) ? POS_INF : x + y; }

    /**
     * Formats the result for leetcode submission as it needs -1 for unreachable nodes
     */
    static inline int format_result(int result) { return result == POS_INF ? -1 : result; }

    /**
     * Builds the reverse adj list where each vertex stores the list
     * of vertices (and weights) from which there is an edge
     * instead of the vertices to which there is an edge
     *
     * Eg: If the edges are (weights omitted for illustration):
     * 0->1, 1->2, 2->0, 1->3, 2->3
     * The reverse adj list will look like:
     * 0: [2],
     * 1: [0],
     * 2: [1],
     * 3: [1, 2]
     */
    static void build_reverse_adj_list(const std::vector<std::vector<int>> &flights,
                                       std::vector<std::vector<std::pair<int, int>>> &reverse_adj_list)
    {
        int from, to, cost;
        for (const std::vector<int> &flight : flights)
        {
            from = flight[0];
            to = flight[1];
            cost = flight[2];
            reverse_adj_list[to].push_back({from, cost});
        }
    }

    /**
     * Bottom up DP solution
     *
     * Theta(k(E + V)) time and Theta(kV) space
     */
    static int sol1(int n, const std::vector<std::vector<int>> &flights,
                    int src, int dst, int k)
    {
        /**
         * ! Was originally dp[v][i] for the length of the shortest path from src to v
         * ! with atmost 'i' edges
         * ! We changed it to dp[i][v] for cache locality as we were filling it column
         * ! by column originally and now we can fill it row by row accessing the values
         * ! in the previous row increasing cache locality
         * * DP solution:
         * dp[i][v]: The length of the shortest path from the src to v
         *           with *atmost* i edges
         * * Base case:
         * dp[i][src] = 0        for all i in [0, k]
         * dp[0][v]   = pos_inf  for all v != src
         * As length of the shortest path from src to itself with atmost k edges (for any k)
         * and length of the shortest path from src to any other vertex with atmost 0 edges
         * is infinity as we can't reach any other node from source with atmost 0 edges
         * * Recurrence relation:
         * Consider the shortest path P from src to v with atmost i-1 edges,
         * then P is either:
         * a. The shortest path from src to v with atmost i-1 edges (or)
         * b. For some u->v, the shortest path from src to u with atmost i-1 edges + the edge u->v
         * dp[i][v] = min{
         *                 dp[i-1][v],
         *                 min{ dp[i-1][u] + l(u, v) for all u->v }
         *               }
         * * Order of filling:
         * Fill each row in any order as dp values in a row depend only upon the
         * values of the previous row
         * * Convergence (early stopping):
         * If for any layer 'i', dp[i][v] = dp[i-1][v] for all vertices 'v', we'd converged
         * and all the further rows are going to be the same.
         * We can stop as we found the shortest distances (all vertices' true shortest distances
         * require less than k edges, so we'd be returning true shortest distances).
         * * Final answer:
         * dp[k][dst]
         * * Running time:
         * #subproblems:        n(k + 1)
         * work per subproblem: Theta(indegree)
         * postprocessing:      Theta(1)
         * sum of indegree in the graph = #edges (handshake lemma)
         * total running time = Theta((k + 1) * #edges) = Theta(k * #edges)
         */

        // k represents the #intermediate stops along the path
        // In our formulation we need k to be the length of the path
        // So we increment k
        // Length of the path = #intermediate stops + 1
        k++;

        // Build a reverse adjacency list (different from an adjacency list for the reverse graph)
        // so that we can keep track of the incoming edges to a vertex instead of the outgoing
        // edges which we do in a normal adjacency list
        // If there is an edge from u->v, u (and the edge's cost) appears in v's adjacency list
        std::vector<std::vector<std::pair<int, int>>> reverse_adj_list(n);
        build_reverse_adj_list(flights, reverse_adj_list);

        // Init the dp table with 0s and fill the base cases
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n));
        for (int v = 0; v < n; v++)
            dp[0][v] = POS_INF;
        dp[0][src] = 0;

        // Fill the table row by row from left to right
        // except for the last row
        for (int i = 1; i < k; i++)
        {
            // At the end of the 'v' for loop, it holds true if for all vertices 'v'
            // dp[i][v] = dp[i-1][v]
            // which means we'd converged
            bool is_row_unchanged{true};

            for (int v = 0; v < n; v++)
            {
                if (v == src)
                    continue;

                int &min_value = dp[i][v];
                min_value = dp[i - 1][v];
                for (const auto &[u, cost] : reverse_adj_list[v])
                    min_value = std::min(min_value, sum(dp[i - 1][u], cost));

                // Check dp[i][v] is the same as dp[i-1][v] for this vertex 'v'
                is_row_unchanged &= (min_value == dp[i - 1][v]);
            }

            // ! Optimization: If none of the values have changed from atmost i-1 edges
            // ! to atmost i edges then they are not further going to change and we can stop
            // ! as we found the shortest distance (all vertices' true shortest distances
            // ! require less than k edges, so we'd be returning true shortest distances)
            if (is_row_unchanged)
                return format_result(dp[i][dst]);
        }

        // ! Optimization: we don't need to fill the entire last row
        // ! as we only need the dp[dst][k] from the last row
        int min_value = dp[k - 1][dst];
        for (const auto &[u, cost] : reverse_adj_list[dst])
            min_value = std::min(min_value, sum(dp[k - 1][u], cost));

        // Return the answer
        return format_result(min_value);
    }

    /**
     * Space optimized version of solution 1
     *
     * Theta(k(E + V)) time and Theta(V) space
     */
    static int sol2(int n, const std::vector<std::vector<int>> &flights,
                    int src, int dst, int k)
    {
        // Increment k and build the reverse adj list
        k++;
        std::vector<std::vector<std::pair<int, int>>> reverse_adj_list(n);
        build_reverse_adj_list(flights, reverse_adj_list);

        // We only need the values of the previous row
        // But we cannot have just one row and update itself (like edit distance etc)
        // as dp[v][i] might need dp[u][i-1] (which would have been updated with dp[u][i] if u < v)
        // We can have a 1d vector storing one row and a temporary 1d row to store the
        // results of computation before we completely get rid of the previous row
        // ! Optimization: To prevent copying to temp vector, we can use 2 rows and use
        // ! one row for dp values and the other for temp alternating
        std::vector<std::vector<int>> dp(2, std::vector<int>(n, POS_INF));

        // For the src vertex, the dp value is always going to be 0
        // and we fill it as we don't compute the dp values for the src in the main loop
        dp[0][src] = 0;
        dp[1][src] = 0;

        for (int i = 1; i < k; i++)
        {
            // The prev_row will be dp[0] if i is odd (initially when i = 1
            // dp[0] is the first row) and the values will be computed and stored in dp[1]
            // And in the next iteration when i is even, dp[1] becomes the prev row
            // and dp[0]'s values aren't obsolete, so we fill the current row's values in dp[0]
            // And we keep alternating

            // We use references to the original rows in the 2d dp array as prev_row and curr_row
            // ! std::vector<int> &prev_row = dp[i % 2 == 1 ? 0 : 1];
            // ! std::vector<int> &curr_row = dp[i % 2 == 1 ? 1 : 0];
            // ! `i % 2 == 1 ? 0 : 1` can be simplified to 1 - (i & 1)
            // ! `i % 2 == 1 ? 1 : 0` can be simplified to (i & 1)
            std::vector<int> &prev_row = dp[1 - (i & 1)];
            std::vector<int> &curr_row = dp[i & 1];

            bool is_row_unchanged{true};

            for (int v = 0; v < n; v++)
            {
                if (v == src)
                    continue;
                int &min_value = curr_row[v];
                min_value = prev_row[v];
                for (const auto &[u, cost] : reverse_adj_list[v])
                    min_value = std::min(min_value, sum(prev_row[u], cost));

                is_row_unchanged &= (min_value == prev_row[v]);
            }

            // Read solution1's explanation for this optimization of convergence
            if (is_row_unchanged)
                return format_result(curr_row[dst]);
        }

        // If k is odd, according to the invariant dp[0] will be the prev row
        // and dp[1] will be the prev row if k is even
        // Optimization: Entire kth row need not be computed, just the dst's index
        // value need to be computed.
        std::vector<int> &prev_row = dp[1 - (k & 1)];
        int min_value = prev_row[dst];
        for (const auto &[u, cost] : reverse_adj_list[dst])
            min_value = std::min(min_value, sum(prev_row[u], cost));

        // Return the answer
        return format_result(min_value);
    }

    /**
     * Memoized recursive function that computes dp[v][i]
     */
    static int compute(std::vector<std::vector<std::pair<int, int>>> &reverse_adj_list,
                       int v, int i,
                       std::vector<std::vector<int>> &memo)
    {
        // Base cases are already memoized
        int &answer = memo[v][i];
        if (answer != -1)
            return answer;

        answer = compute(reverse_adj_list, v, i - 1, memo);
        for (const auto &[u, cost] : reverse_adj_list[v])
            answer = std::min(answer, sum(compute(reverse_adj_list, u, i - 1, memo), cost));
        return answer;
    }

    /**
     * Top down DP version of solution 1
     *
     * This is potentially better as we don't have to compute the
     * dp[v][i] values for all vertices 'v' for a certain 'i'
     * Top down approach only computes the values that are required
     */
    static int sol3(int n, const std::vector<std::vector<int>> &flights,
                    int src, int dst, int k)
    {
        // Increment k and build the reverse adj list
        k++;
        std::vector<std::vector<std::pair<int, int>>> reverse_adj_list(n);
        build_reverse_adj_list(flights, reverse_adj_list);

        // Store the base case values in the memo so that we don't need to have
        // a separate condition for the base case in the recursive function
        std::vector<std::vector<int>> memo(n, std::vector<int>(k + 1, -1));
        for (int v = 0; v < n; v++)
            memo[v][0] = POS_INF;
        for (int i = 0; i <= k; i++)
            memo[src][i] = 0;

        // Recursively compute dp[dst][k] and return the answer
        int result = compute(reverse_adj_list, dst, k, memo);
        return format_result(result);
    }

public:
    int findCheapestPrice(int n, const std::vector<std::vector<int>> &flights,
                          int src, int dst, int k) { return sol3(n, flights, src, dst, k); }
};