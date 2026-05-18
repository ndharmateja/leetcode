#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

class Solution
{
private:
    static inline const int POS_INF = std::numeric_limits<int>::max();

    static int sum(int x, int y)
    {
        if (x == POS_INF || y == POS_INF)
            return POS_INF;
        return x + y;
    }

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
        k++;

        std::vector<std::vector<std::pair<int, int>>> reverse_adj_list(n);
        for (const std::vector<int> &flight : flights)
        {
            int from = flight[0];
            int to = flight[1];
            int cost = flight[2];
            reverse_adj_list[to].push_back({from, cost});
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(k + 1));
        for (int v = 0; v < n; v++)
            dp[v][0] = POS_INF;
        dp[src][0] = 0;

        for (int i = 1; i < k; i++)
            for (int v = 0; v < n; v++)
            {
                if (v == src)
                    continue;
                int min_value = dp[v][i - 1];
                for (const auto &[u, cost] : reverse_adj_list[v])
                    min_value = std::min(min_value, sum(dp[u][i - 1], cost));
                dp[v][i] = min_value;
            }

        int min_value = dp[dst][k - 1];
        for (const auto &[u, cost] : reverse_adj_list[dst])
            min_value = std::min(min_value, sum(dp[u][k - 1], cost));

        return min_value == POS_INF ? -1 : min_value;
    }

    /**
     * Space optimized version of solution 1
     */
    static int sol2(int n, const std::vector<std::vector<int>> &flights,
                    int src, int dst, int k)
    {
        // Increment k and build the reverse adj list
        k++;
        std::vector<std::vector<std::pair<int, int>>> reverse_adj_list(n);
        build_reverse_adj_list(flights, reverse_adj_list);

        // We only need the values of the previous column
        // But we cannot have just one column and update itself (like edit distance etc)
        // as dp[v][i] might need dp[u][i-1] (which would have been updated with dp[u][i] if u < v)
        // We can have a 1d vector storing one column and a temporary 1d column to store the
        // results of computation before we completely get rid of the previous column
        // ! Optimization: To prevent copying to temp vector, we can use 2 columns and use
        // ! one column for dp values and the other for temp alternating
        // ! We are storing the 2 columns as 2 rows for cache locality
        std::vector<std::vector<int>> dp(2, std::vector<int>(n, POS_INF));

        // For the src vertex, the dp value is always going to be 0
        // and we fill it as we don't compute the dp values for the src in the main loop
        dp[0][src] = 0;
        dp[1][src] = 0;

        for (int i = 1; i < k; i++)
        {
            // The prev_col will be dp[0] if i is odd (initially when i = 1
            // dp[0] is the first column) and the values will be computed and stored in dp[1]
            // And in the next iteration when i is even, dp[1] becomes the prev col
            // and dp[0]'s values aren't obsolete, so we fill the current col's values in dp[0]
            // And we keep alternating

            // We use references to the original rows in the 2d dp array as prev_col and curr_col
            std::vector<int> &prev_col = dp[i % 2 == 1 ? 0 : 1];
            std::vector<int> &curr_col = dp[i % 2 == 1 ? 1 : 0];
            for (int v = 0; v < n; v++)
            {
                if (v == src)
                    continue;
                int min_value = prev_col[v];
                for (const auto &[u, cost] : reverse_adj_list[v])
                    min_value = std::min(min_value, sum(prev_col[u], cost));
                curr_col[v] = min_value;
            }
        }

        // If k is odd, according to the invariant dp[0] will be the prev col
        // and dp[1] will be the prev col if k is even
        // Optimization: Entire kth col need not be computed, just the dst's index
        // value need to be computed.
        std::vector<int> &prev_col = dp[k % 2 == 1 ? 0 : 1];
        int min_value = prev_col[dst];
        for (const auto &[u, cost] : reverse_adj_list[dst])
            min_value = std::min(min_value, sum(prev_col[u], cost));

        // Return the answer
        return min_value == POS_INF
                   ? -1
                   : min_value;
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

    // static int sol2(int n, const std::vector<std::vector<int>> &flights,
    //                 int src, int dst, int k)
    // {
    // }

public:
    int findCheapestPrice(int n, const std::vector<std::vector<int>> &flights,
                          int src, int dst, int k) { return sol1(n, flights, src, dst, k); }
};