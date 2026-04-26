#include <limits>
#include <vector>

class Solution
{
    static inline const int pos_inf = std::numeric_limits<int>::max();

    /**
     * Bottom up DP
     */
    static int solution1(const std::vector<int> &coins, int amount)
    {
        // Edge case
        if (amount == 0)
            return 0;

        // DP solution:
        // dp[i]: the min number of coins required to make up amount i or -1 if it can't be formed
        // Base case:
        // dp[0] = 0
        // Recurrence:
        // dp[i] = min{dp[i - d] for each denomination d <= i} + 1
        // Order of filling:
        // From left to right
        // Final answer: dp[amount]

        // Create the dp array and fill it with -1 so that we don't have to
        // update it if we don't find a solution
        std::vector<int> dp(amount + 1, -1);

        // Base case
        dp[0] = 0;

        // Fill the table
        for (int i = 1; i <= amount; i++)
        {
            // Find the min coins required to make up i - coin for each of the coins
            int min_coins = pos_inf;
            for (int coin : coins)
            {
                // If coin itself is larger than i, we can skip this coin
                if (coin > i)
                    continue;

                // If the amount 'i-coin' couldn't also be made up
                // then we can skip this coin
                int prev_min_coins = dp[i - coin];
                if (prev_min_coins == -1)
                    continue;

                // Otherwise see if this is the min number of coins
                min_coins = prev_min_coins < min_coins ? prev_min_coins : min_coins;
            }

            // At this point if min_coins is still pos_inf, it means that i cannot be formed
            // using the given coins
            if (min_coins == pos_inf)
                continue;

            // Otherwise we can compute the min coins for i as min_coins + 1
            dp[i] = min_coins + 1;
        }

        // Return the result
        return dp[amount];
    }

public:
    int coinChange(const std::vector<int> &coins, int amount) { return solution1(coins, amount); }
};