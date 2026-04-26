#include <string>
#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP solution
     *
     * Theta(mn) time and Theta(mn) space solution
     * where m = len(s1) and n = len(s2)
     */
    static int solution1(const std::string &s1, const std::string &s2)
    {
        // DP solution:
        // say m = len(s1), n = len(s2), LCS = longest common subsequence
        // dp[i][j]: the length of the LCS between s1[:i] which is a prefix of s1 of length i
        //           and s2[:j] which is a prefix of s2 of length j (python notation)
        // Base cases: dp[0][.] = dp[.][0] = 0 as the LCS between an empty string and anything
        //             is just the empty string
        // Recurrence relation:
        // dp[i][j] = dp[i-1][j-1] + 1             if s1[i-1] == s2[j-1]
        //          = max{dp[i][j-1], dp[i-1][j]}  otherwise
        // Order of filling the table:
        // We fill row by row going from left to right as we need the top value, the left value
        // and the top left values
        // Final answer: dp[m][n]

        // The DP array has to be of size m+1 x n+1
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())};
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        // Base cases
        // Fill the first column with 0s
        for (int i = 0; i <= m; i++)
            dp[i][0] = 0;
        // Fill the first row with 0s
        for (int j = 1; j <= n; j++)
            dp[0][j] = 0;

        // Fill the DP table row by row from left to right
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = s1[i - 1] == s2[j - 1]
                               ? dp[i - 1][j - 1] + 1
                               : std::max(dp[i - 1][j], dp[i][j - 1]);

        // Return the answer
        return dp[m][n];
    }

    /**
     * Space optimized bottom up DP. Using a 1xn array (exchange s1 and s2 to keep
     * n as the smaller if necessary). Use a temporary variable to keep of the top left
     * as that would be overwritten as we are using a 1xn array
     *
     * Theta(mn) time and Theta(min{m, n}) space solution
     * where m = len(s1) and n = len(s2)
     */
    static int solution2(const std::string &text1, const std::string &text2)
    {
        // Make sure that n < m to optimize space further
        // so that s2 will always have the smaller string
        // Create references s1 and s2 accordingly
        const std::string &s1 = text1.size() <= text2.size() ? text2 : text1;
        const std::string &s2 = text1.size() <= text2.size() ? text1 : text2;

        // Create a row filled with 0s
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())};
        std::vector<int> dp_row(n + 1);

        // Compute the DP values row by row but overwriting the same vector with the new values
        for (int i = 1; i <= m; i++)
        {
            int previous_top_left = 0;
            for (int j = 1; j <= n; j++)
            {
                // Store the value at j as the next iteration's top left
                int temp = dp_row[j];

                // DP update
                dp_row[j] = s1[i - 1] == s2[j - 1]
                                ? previous_top_left + 1
                                : std::max(dp_row[j - 1], dp_row[j]);

                // Update the top left value for the next iteration
                previous_top_left = temp;
            }
        }

        // Return the result
        return dp_row[n];
    }

public:
    int longestCommonSubsequence(const std::string &s1, const std::string &s2) { return solution2(s1, s2); }
};