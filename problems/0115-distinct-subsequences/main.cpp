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
     * where m = len(s) and n = len(t)
     */
    static long long solution1(const std::string &s, const std::string &t)
    {
        /**
         * * DP Solution:
         * * Eg: s=BABGBAG, t=BAG
         * B A B G B A G
         * B A   G
         * B A         G
         *     B     A G
         *         B A G
         * BAG occurs in BABGBAG as 4 distinct subsequences
         *
         * * Definition
         * dp[i][j]: the number of distinct ways t[:j] which is a prefix of t of length j can
         *           be written as a subsequence of s[:i] which is a prefix of s of length i
         *
         * * Base cases
         * 1. If t[:j] is empty, then it can be written as 1 distinct subsequence of s
         *    irrespective of how many characters there are in s
         *        dp[i][0] = 1 for 0 <= i <= m
         * 2. If t[:j]'s length (which is j) is greater than s[:i]'s length (which is i)
         *    then the number of ways t[:j] can be written as a subsequence of s[:i] is 0
         *        dp[i][j] = 0 for j > 0 and i < j
         *
         * * Recurrence relation:
         * B A B G B A G X
         * B A   G
         * B A         G
         *     B     A G
         *         B A G
         * If the last characters aren't same, then the number of distinct subsequences
         * is the same as removing the last character (X) of the bigger string (# distinct
         * subsequences of BAG in BABGBAG)
         *
         * B A B G B A G
         * B A   G
         * B A         G
         *     B     A G
         *         B A G
         * If they match, the last character G of the bigger string can be included or excluded
         * We can remove the last char (say G) and count the number of distinct
         * subsequences which include the common char (# distinct subsequences of BA in BABGBA
         * and appending G to all those subsequences) => dp[i-1][j-1]
         * And then also count the number of distinct subsequences that exclude the last G of the
         * bigger string (# distinct subsequences of BAG in BABGBA) => dp[i-1][j]
         * and add them both up
         * dp[i][j] = dp[i-1][j-1] + dp[i-1][j]  if s[i-1] == t[j-1]
         *          =                dp[i-1][j]  otherwise
         *
         * Note:
         * Since each value depends only on the value above and on the value on top left
         * we don't need the bottom left values below the diagonal computed.
         * So if i - j > m - n, then we don't need those values.
         *
         * * Example table
         *          j
         *       0 1 2 3
         *       . B A G
         *   0 . 1 0 0 0
         *        ↘↓
         *   1 B 1 1 0 0
         *         ↓↘↓
         *   2 A 1 1 1 0
         *        ↘↓ ↓ ↓
         *   3 B 1 2 1 0
         *         ↓ ↓↘↓
         * i 4 G 1 2 1 1
         *        ↘↓ ↓ ↓
         *   5 B - 3 1 1
         *          ↘↓ ↓
         *   6 A - - 4 1
         *            ↘↓
         *   7 G - - - 5
         *
         * * Order of filling the table:
         * We can fill row by row going from left to right as we only need the
         * value on the top left and value on the top
         *
         * * Final answer: dp[m][n]
         */

        // Base cases
        if (s == t)
            return 1;
        int m{static_cast<int>(s.size())}, n{static_cast<int>(t.size())};
        if (m < n)
            return 0;

        // The DP array has to be of size m+1 x n+1
        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1));

        // Base cases
        // Fill the first column with 0s
        for (int i = 0; i <= m; i++)
            dp[i][0] = 1;
        // Fill the first row with 0s
        for (int j = 1; j <= n; j++)
            dp[0][j] = 0;

        // Fill the DP table row by row from left to right
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (i - j > m - n)
                    continue;
                if (i < j)
                    dp[i][j] = 0;
                else if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }

        // Return the answer
        return dp[m][n];
    }

    /**
     * Top down version of solution1
     * Theta(mn) time and Theta(mn) space (for the memo) in the worst case
     *
     * This solution is preferable as it only computes what is necessary in the table
     * instead of all the values. Even if we don't calculate bottom left values
     * below the diagonal it still might compute values that aren't necessary.
     *
     * TODO: use a hashmap for the memo i * n + j as the key so that the unordered_map<int, int> works
     * TODO: implement a space optimized version of the bottom up DP approach Theta(n) space
     */
    static int solution2(const std::string &s, const std::string &t, int i, int j, std::vector<std::vector<int>> &memo)
    {
        // If memo contains the answer, we can return it
        if (memo[i][j] != -1)
            return memo[i][j];

        // Base cases
        if (j == 0)
            memo[i][j] = 1;
        else if (i < j)
            memo[i][j] = 0;

        // General recurrence cases
        else if (s[i - 1] == t[j - 1])
            memo[i][j] = solution2(s, t, i - 1, j - 1, memo) + solution2(s, t, i - 1, j, memo);
        else
            memo[i][j] = solution2(s, t, i - 1, j, memo);

        // Return the answer
        return memo[i][j];
    }

    static int solution2(const std::string &s, const std::string &t)
    {
        // We use -1 values as sentinel values to indicate that the values weren't computed
        int m{static_cast<int>(s.size())}, n{static_cast<int>(t.size())};
        std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, -1));
        return solution2(s, t, m, n, memo);
    }

public:
    int numDistinct(const std::string &s, const std::string &t) { return solution2(s, t); }
};
