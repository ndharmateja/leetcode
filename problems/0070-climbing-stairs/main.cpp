#include <vector>

class Solution
{
private:
    /**
     * Bottom up DP
     */
    static int solution1(int n)
    {
        // DP solution
        //         ___
        //     ___|
        // ___|_______
        //  0   1   2
        // To reach step 2, we can either reach from step 0 using 2 steps
        // or reach from step 1 using 1 step
        // so the number of ways to reach step 2 is 2
        // dp[i]: Number of ways to reach step 'i'
        // Base case:
        // dp[0] = 1
        // dp[1] = 1
        // Recurrence relation:
        // dp[i] = dp[i-1] + dp[i-2]
        // Order of filling: from left to right
        // Final answer: dp[n]

        // Note: This is very similar to the fibonacci number problem
        std::vector<int> dp(n + 1);

        // Base cases
        dp[0] = 1;
        dp[1] = 1;

        // Fill the table
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i - 1] + dp[i - 2];

        // Return the answer
        return dp[n];
    }

    /**
     * Space optimized bottom up DP
     */
    static int solution2(int n)
    {
        if (n == 1)
            return 1;

        int prev2{1}, prev1{1}, curr;
        for (int i = 2; i <= n; i++)
        {
            curr = prev2 + prev1;
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }

public:
    int climbStairs(int n) { return solution1(n); }
};