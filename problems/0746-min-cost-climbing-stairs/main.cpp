#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP solution
     */
    static int solution1(std::vector<int> &cost)
    {
        // DP solution:
        // n = len(cost) => last step = n-1
        // dp[i]: min cost to reach step 'i'
        // Base case:
        // dp[0] = dp[1] = 0
        // Recurrence:
        // dp[i] = min{ dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]}
        // Order of filling:
        // from left to right
        // Final answer: dp[n]
        int n{static_cast<int>(cost.size())};
        std::vector<int> dp(n + 1);

        // Base cases
        dp[0] = dp[1] = 0;

        // Fill the table
        for (int i = 2; i <= n; i++)
            dp[i] = std::min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);

        // Return the result
        return dp[n];
    }

    /**
     * Space optimized bottom up DP solution
     */
    static int solution1(std::vector<int> &cost)
    {
        int n{static_cast<int>(cost.size())};
        int prev_cost_2{0}, prev_cost_1{0}, curr_cost;
        for (int i = 2; i <= n; i++)
        {
            curr_cost = std::min(prev_cost_2 + cost[i - 2], prev_cost_1 + cost[i - 1]);
            prev_cost_2 = prev_cost_1;
            prev_cost_1 = curr_cost;
        }
        return curr_cost;
    }

public:
    int minCostClimbingStairs(std::vector<int> &cost) { return solution1(cost); }
};