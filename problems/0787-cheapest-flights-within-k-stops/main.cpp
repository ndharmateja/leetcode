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

    // static int sol2(std::vector<std::vector<std::pair<int, int>>> reverse_adj_list,
    //                 int v, int i, int src)
    // {
    //     if (v == src)
    //         return 0;
    //     if (i == 0)
    //         return POS_INF;

    // }

    // static int sol2(int n, const std::vector<std::vector<int>> &flights,
    //                 int src, int dst, int k)
    // {
    // }

public:
    int findCheapestPrice(int n, const std::vector<std::vector<int>> &flights,
                          int src, int dst, int k) { return sol1(n, flights, src, dst, k); }
};