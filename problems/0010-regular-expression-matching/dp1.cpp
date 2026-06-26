#include <string>
#include <vector>

class Solution
{
private:
    static constexpr bool is_match(int i, int j, int n, const std::string &text,
                                   const std::string &re) { return (i < n) && ((text[i] == re[j]) || (re[j] == '.')); }

    /**
     * Bottom up DP solution
     *
     * Theta(mn) time and Theta(mn) space
     * where m = len(pattern) and n = len(text)
     */
    static bool sol3(const std::string &text, const std::string &re)
    {
        /**
         * ! Note: there are n+1 rows (as dimension i tracks the text), so 0 <= i <= n
         * ! and m+1 cols (as dimension j tracks the re), so 0 <= j <= m
         *
         * * DP solution
         * dp[i][j] := true   if text[i:] can be matched with re[j:]
         *             false  otherwise
         * * Base cases
         * dp[n][j] = true   if j == m (an empty regex can match an empty string)
         *          = false  otherwise (an empty regex cannot match a non-empty string)
         * * Recurrence relation
         * match(i, j) := (i < n) && (text[i] == re[j] || re[j] == '.')
         * match(i, j) is true if i is a valid index in the text and it matches with re[j]
         *
         * dp[i][j] = false                            if re[j] == '*'
         *                                              (the regex can't start with a '*')
         *          = dp[i][j+2]                       if j + 1 < m && re[j+1] = '*'
         *             || (match(i, j) && dp[i+1][j])   (if the next character is a * in the re)
         *          = match(i, j) && dp[i+1][j+1]      otherwise
         *                                              (j < m && re[j] != '*' && re[j+1] != '*')
         * * Order of filling
         * We need the values on the bottom, bottom right, two steps to the right
         * so we fill the table row by row going from bottom to top filling
         * each row from right to left
         * * Final answer
         * dp[0][0]
         * * Running time
         *       # subproblems = (m+1)(n+1)
         * work per subproblem = Theta(1)
         *          total work = Theta(mn)
         */

        // Create the DP table
        int n(static_cast<int>(text.size())), m{static_cast<int>(re.size())};
        std::vector<std::vector<char>> dp(n + 1, std::vector<char>(m + 1, false));

        // Base cases
        // The dp table is init with false, so we don't have to explicitly set false
        dp[n][m] = true;

        // Fill the table
        for (int i = n; i >= 0; i--)
            for (int j = m - 1; j >= 0; j--)
            {
                // If re[j] is a '*', this should be false
                // but we don't need to explicitly set it
                if (re[j] == '*')
                    continue;

                // Handle the case where the next character in the re is a '*'
                if (j + 1 < m && re[j + 1] == '*')
                    dp[i][j] = dp[i][j + 2] || (is_match(i, j, n, text, re) && dp[i + 1][j]);

                // Handle the remaining case (where re[j] is a normal character or '.')
                else
                    dp[i][j] = is_match(i, j, n, text, re) && dp[i + 1][j + 1];
            }

        // Return the answer
        return dp[0][0];
    }

    /**
     * TODO: Space optimized version of solution 3
     *
     * Theta(mn) time and Theta(m) space
     * where m = len(pattern) and n = len(text)
     */
    static bool sol4(const std::string &text, const std::string &re) { return false; }

    static bool recurse(const int i, const int j, const int n, const int m,
                        const std::string &text, const std::string &re,
                        std::vector<std::vector<int8_t>> &memo)
    {
        // If the answer is in the memo, we return it
        int8_t &result = memo[i][j];
        if (result != -1)
            return result;

        // Base cases
        if (j == m)
        {
            result = i == n;
            return result;
        }

        // If re[j] is a '*', this should be false
        // but we don't need to explicitly set it
        if (re[j] == '*')
        {
            result = false;
            return result;
        }

        // Handle the case where the next character in the re is a '*'
        if (j + 1 < m && re[j + 1] == '*')
            result = recurse(i, j + 2, n, m, text, re, memo) ||
                     (is_match(i, j, n, text, re) && recurse(i + 1, j, n, m, text, re, memo));

        // Handle the remaining case (where re[j] is a normal character or '.')
        else
            result = is_match(i, j, n, text, re) && recurse(i + 1, j + 1, n, m, text, re, memo);

        // Return the answer
        return result;
    }

    /**
     * Top down version of solution 3
     *
     * Theta(mn) time and Theta(mn) space
     * where m = len(pattern) and n = len(text)
     */
    static bool sol5(const std::string &text, const std::string &re)
    {
        // Create the memo and recurse and return the result
        int n(static_cast<int>(text.size())), m{static_cast<int>(re.size())};
        std::vector<std::vector<int8_t>> memo(n + 1, std::vector<int8_t>(m + 1, -1));
        return recurse(0, 0, n, m, text, re, memo);
    }

public:
    bool isMatch(const std::string &text, const std::string &re) { return sol5(text, re); }
};