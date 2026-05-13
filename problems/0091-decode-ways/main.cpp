#include <string>
#include <vector>

class Solution
{
private:
    /**
     * Bottom up DP approach
     *
     * Theta(n) time and Theta(n) space solution
     */
    static int sol1(const std::string &s)
    {
        /**
         * * DP solution
         * dp[i]: number of ways to decode s[i:]
         * * Base case
         * dp[n] = 1 as there is trivially one way to decode empty string
         * * Recurrence relation
         * dp[i] = 0                                                 if s[i] == '0'
         *       = dp[i+1] + (10 <= s[i:i+2] <= 26 ? dp[i+2] : 0)    otherwise
         * There are 0 ways to decode a string starting with 0.
         * If s[i] is not a 0, then we can decode s[i:] atleast in as many as ways
         * as s[i+i:] by prepending s[i] to each of the ways we can decode s[i+1:].
         * And if s[i:i+2] is also a valid alphabet number (in [10, 26] range),
         * then we can additionally decode s[i:] in as many ways as s[i+2:]
         * by prepending s[i:i+2] to each of those ways
         * * Order of filling
         * From right to left as we need dp[i+1] and dp[i+2]
         * * Final answer
         * dp[0]
         * * Running time
         * #subproblems: n+1
         * work per subproblem: Theta(1)
         * postprocessing: Theta(1)
         * total running time : Theta(n)
         */

        // Create the dp array
        int n{static_cast<int>(s.size())};
        std::vector<int> dp(n + 1, 0);

        // Base cases
        // We can fill in both dp[n] and dp[n-1]
        // to avoid if conditions inside the main loop
        // dp[n-1] is 1 if s[n-1] is not a 0 (true evaluates to 1)
        dp[n] = 1;
        dp[n - 1] = s[n - 1] != '0';

        // Fill the dp table
        for (int i = n - 2; i >= 0; i--)
        {
            // If s[i] is a 0 then dp[i] = 0 as we can decode s[i:] in 0 ways
            unsigned char curr = s[i];
            if (curr == '0')
                continue;

            // If we reach here then we have a non-zero digit in s[i]
            // So we can atleast decode s[i:] in as many ways as s[i+1:]
            dp[i] += dp[i + 1];

            // If s[i:i+2] forms a number in the range [10, 26] we can add
            // dp[i+2] as well to dp[i]
            unsigned char next = s[i + 1];
            if ((curr == '1') ||
                (curr == '2' && '0' <= next && next <= '6'))
                dp[i] += dp[i + 2];
        }

        // Return the answer
        return dp.front();
    }

    /**
     * Space optimized bottom up DP approach
     *
     * Theta(n) time and Theta(1) space solution
     */
    static int sol2(const std::string &s)
    {
        int n{static_cast<int>(s.size())};
        int dp1{s[n - 1] != '0'}, dp2{1};

        for (int i = n - 2; i >= 0; i--)
        {
            // If s[i] is a 0 then dp[i] = 0 as we can decode s[i:] in 0 ways
            unsigned char curr = s[i];
            if (curr == '0')
            {
                dp2 = dp1;
                dp1 = 0;
                continue;
            }

            // If we reach here then we have a non-zero digit in s[i]
            // So we can atleast decode s[i:] in as many ways as s[i+1:]
            int dp0{dp1};

            // If s[i:i+2] forms a number in the range [10, 26] we can add
            // dp[i+2] as well to dp[i]
            unsigned char next = s[i + 1];
            if ((curr == '1') ||
                (curr == '2' && '0' <= next && next <= '6'))
                dp0 += dp2;

            // Update the dp values for the next iteration
            dp2 = dp1;
            dp1 = dp0;
        }

        // Return the answer
        return dp1;
    }

    /**
     * Recursive function (memoized) that computes the #ways we can decode s[i:]
     */
    static int sol3(const std::string &s, int i, int n, std::vector<int> &memo)
    {
        // Edge case
        // If string starts with 0, then 0 ways
        if (s[i] == '0')
            return 0;

        // Base case
        // If index out of bounds, we can return 1
        if (i == n)
            return 1;

        // If memo contains the answer we can directly return it
        int &answer = memo[i];
        if (answer != -1)
            return answer;

        // We can try to form a number with just s[i] or s[i:i+2]
        // At this point we know that s[i] is non zero
        // So we can form a number with s[i]
        answer = sol3(s, i + 1, n, memo);

        // We can form a number with s[i:i+2] if there are two digits and
        // it forms a number between 10 and 26
        if (i <= n - 2 &&
            ((s[i] == '1') ||
             (s[i] == '2' && '0' <= s[i + 1] && s[i + 1] <= '6')))
            answer += sol3(s, i + 2, n, memo);

        // Return the answer
        return answer;
    }

    /**
     * Top down DP approach
     */
    static int sol3(const std::string &s)
    {
        int n{static_cast<int>(s.size())};
        std::vector<int> memo(n, -1);
        return sol3(s, 0, n, memo);
    }

public:
    int numDecodings(const std::string &s) { return sol2(s); }
};