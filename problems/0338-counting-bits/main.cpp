#include <vector>

class Solution
{
private:
    /**
     * Bottom up DP solution
     * Theta(n) time and Theta(1) space
     */
    static std::vector<int> solution1(int n)
    {
        // Create the result vector of size n+1
        std::vector<int> result(n + 1);

        /**
         * * DP Solution
         * dp[i]: #bits in i
         *
         * * Base case
         * dp[0] = 0
         *
         * * Recurrence relation
         *      dp[i] = dp[i >> 1] + (i mod 2)
         * (or) dp[i] = dp[i >> 1] + (i & 1)
         *
         * * Order of filling the table
         * from left to right as we only need the dp value of i/2
         */

        // To simplify (i mod 2) or (i & 1) we maintain a bool parity variable that will be considered as 0 or 1
        // We start with parity = 1 as the first i we are dealing with is i = 1
        // For i = 0, the #bits is 0 and that is taken care of in the initialization
        bool parity = 1;
        for (int i = 1; i <= n; i++)
        {
            result[i] = result[i >> 1] + parity;
            parity = !parity;
        }
        return result;
    }

    /**
     * Same solution as above without the parity variable
     * Theta(n) time and Theta(1) space
     */
    static std::vector<int> solution2(int n)
    {
        std::vector<int> result(n + 1);
        for (int i = 1; i <= n; i++)
            result[i] = result[i >> 1] + (i & 1);

        return result;
    }

public:
    std::vector<int> countBits(int n) { return solution1(n); }
};