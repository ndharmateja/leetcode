#include <string>
#include <vector>

class Solution
{
private:
    /**
     * Bottom up DP solution
     *
     * Theta(mn) time and Theta(mn) space solution
     * where m = len(s1) and n = len(s2)
     */
    static bool solution1(const std::string &s1, const std::string &s2, const std::string &s3)
    {
        /**
         * * DP solution:
         * dp[i][j]: Keeps track of if s1[:i] which is the prefix of s1 of length i
         *           and s2[:j] which is the prefix of s2 of length j can be interleaved
         *           to form s3[:i+j] which is the prefix of s3 of length i+j
         *
         * * Base case:
         * dp[0][0] = true as two empty strings can be interleaved to form an empty string
         *
         * * Recurrence relation:
         * 1. For the first column in the table, j=0 => we are checking if s1[:i] and ""
         *    can be interleaved to form s3[:i] which means we are checking if s1[:i] and s3[:i]
         *    are the same, which can be checked by seeing if the last characters are same and
         *    if s1[:i-1] and "" can be interleaved to form s3[:i-1]
         *        dp[i][0] = (s1[i-1] == s3[i-1]) && dp[i-1][0] for i > 0
         * 2. Similarly for the first row in the table, where i=0
         *        dp[0][j] = (s2[j-1] == s3[j-1]) && dp[0][j-1] for j > 0
         * 3. For the general case where i > 0 and j > 0,
         *    a. if the last chars of s1[:i] and s3[:i+j] are same, then we need to check
         *    if s1[:i-1] and s2[:j] can be interleaved to form s3[:i+j-1] (as we can add the last char to
         *    interleave after)
         *    b. or similarly if last chars of s2[:j] and s3[:i+j] are same, we can do something similar
         *    c. if the none of the above cases occur (the last char of s1 or s2 not same as last char of s3)
         *    then we can't interleave
         *        dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) || (s2[j-1] == s3[i+j-1] && dp[i][j-1])
         *
         * * Order of filling:
         * We fill the table row by row going from left to right in each row as we need the values
         * on the left and top
         *
         * * Final answer: dp[m][n]
         */
        // Edge case: if lengths of s1 and s2 don't add up to s3 then we can't interleave
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())}, p{static_cast<int>(s3.size())};
        if (m + n != p)
            return false;

        // Create the DP table and base case
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1));
        dp[0][0] = true;

        // Fill the first column and the first row
        for (int i = 1; i <= m; i++)
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
        for (int j = 1; j <= n; j++)
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];

        // Fill the table
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                           (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);

        // Return the result
        return dp[m][n];
    }

    /**
     * Space optimized version of solution1
     *
     * Theta(mn) time and Theta(min{m, n}) space solution
     * where m = len(s1) and n = len(s2)
     */
    static bool solution1(const std::string &str1, const std::string &str2, const std::string &s3)
    {
        // Exchange strings 1 and 2 such that s2 is shorter so that the length of the row
        // we are storing in the dp is smaller
        const std::string &s1 = (str1.size() <= str2.size()) ? str2 : str1;
        const std::string &s2 = (str1.size() <= str2.size()) ? str1 : str2;

        // Edge case: if lengths of s1 and s2 don't add up to s3 then we can't interleave
        int m{static_cast<int>(s1.size())}, n{static_cast<int>(s2.size())}, p{static_cast<int>(s3.size())};
        if (m + n != p)
            return false;

        // We don't store the whole DP table
        // We only store one row and compute it row by row
        std::vector<bool> dp_row(n + 1);

        // Base case and compute the first row
        dp_row[0] = true;
        for (int j = 1; j <= n; j++)
            dp_row[j] = (s2[j - 1] == s3[j - 1]) && dp_row[j - 1];

        // Compute the DP table row by row
        for (int i = 1; i <= m; i++)
        {
            // First element in the row depends upon the first element of the previous row (which
            // is stored in dp[0] itself at the start of the iteration)
            dp_row[0] = s1[i - 1] == s3[i - 1] && dp_row[0];

            // dp[i-1][j] is stored in dp[j] itself
            // dp[i][j-1] would have been computed in the previous iteration of j
            // and will be in dp[j-1]
            for (int j = 1; j <= n; j++)
                dp_row[j] = (dp_row[j] && s1[i - 1] == s3[i + j - 1]) ||
                            (dp_row[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }

        // Return the result
        return dp_row[n];
    }

public:
    bool isInterleave(const std::string &s1, const std::string &s2, const std::string &s3) { return solution1(s1, s2, s3); }
};