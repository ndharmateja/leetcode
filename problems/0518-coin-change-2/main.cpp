#include <vector>

class Solution
{
private:
    static int solution1(int amount, const std::vector<int> &coins)
    {
        // DP solution
        // dp[i]: #ways we can make up 'i' using given coins
        //
        // Base case:
        // dp[0] = 1
        //
        // Recurrence:
        // dp[i] = sum{dp[i-coin] such that i >= coin}
        //
        // Order of filling: from left to right
        //
        // Final answer: dp[amount]
        std::vector<int> dp(amount + 1);

        // Base case
        dp[0] = 1;

        // Fill the table
        for (int i = 1; i <= amount; i++)
            for (int coin : coins)
            {
                if (coin <= i)
                    dp[i] += dp[i - coin];
            }

        // Return the result
        return dp[amount];
    }

public:
    int change(int amount, const std::vector<int> &coins) { return solution1(amount, coins); }
};