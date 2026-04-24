#include <vector>

class Solution
{
private:
    static int n_c_r(int n, int r)
    {
        // c(n, r) = c(n, n - r)
        // so if n - r is smaller it is easier to compute
        if (n - r < r)
            r = n - r;

        // c(n, r) = product (1 <= i <= r) (n - r + i)/i
        // We perform the multiplication first and then divide and that works
        // as the product of k consecutive numbers is divisible by k!
        // So we store the result in long long as the numerator product could go
        // out of int bounds even though the final answer doesn't
        long long result = 1;
        for (int i = 1; i <= r; i++)
            result = (result * (n - r + i)) / i;

        // According to leetcode constraints the result will fit in an int
        return static_cast<int>(result);
    }

    static int solution1(int m, int n)
    {
        // If there are m rows, then we have to eventually go down m-1 number of times
        // and similarly we have to go right n-1 number of times
        // So the result is number of ways of permuting m-1 Ds and n-1 Rs
        return n_c_r((m - 1) + (n - 1), n - 1);
    }

    /**
     * DP solution
     */
    static int solution2(int m, int n)
    {
        // Init the dp array
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        // dp[r][c]: stores the #unique ways to reach (r, c)
        // DP recurrence relation:
        // dp[r][c] = dp[r][c-1] + dp[r-1][c]
        // Base case:
        // dp[0][c] = dp[r][0] = 1
        // Order of filling the table: row by row going from left to right
        // Final answer: dp[m-1][n-1]

        // Fill the base case values
        // Fill the first column with 1s
        for (int r = 0; r < m; r++)
            dp[r][0] = 1;
        // Fill the first row with 1s
        for (int c = 1; c < n; c++)
            dp[0][c] = 1;

        // Fill the DP table
        for (int r = 1; r < m; r++)
            for (int c = 1; c < n; c++)
                dp[r][c] = dp[r][c - 1] + dp[r - 1][c];

        // The answer is the bottom right cell
        return dp[m - 1][n - 1];
    }

    /**
     * Space optimized DP solution
     * See solution 2 for more details
     * Each row once done is only necessary for the computing the next row
     * so we have only one 1D row to store the dp values and we use the same vector
     */
    static int solution3(int m, int n)
    {
        std::vector<int> row(n, 1);
        for (int r = 1; r < m; r++)
            for (int c = 1; c < n; c++)
                row[c] = row[c - 1] + row[c];
        return row[n - 1];
    }

    static int solve(int m, int n, std::vector<std::vector<int>> &memo)
    {
        if (memo[m][n] != -1)
            return memo[m][n];
        if (m == 0 || n == 0)
            memo[m][n] = 1;
        else
            memo[m][n] = solve(m - 1, n, memo) + solve(m, n - 1, memo);
        return memo[m][n];
    }

    /**
     * Top down DP solution
     * See solution 2 for more details
     */
    static int solution4(int m, int n)
    {
        // Fill memo with -1s to indicate that value hasn't been computed yet
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        return solve(m - 1, n - 1, memo);
    }

public:
    int uniquePaths(int m, int n) { return solution4(m, n); }
};