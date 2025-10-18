@SuppressWarnings("unused")
class Solution62 {
    private int solution1(int m, int n) {
        // Make sure that m <= n
        if (m > n) {
            int temp = m;
            m = n;
            n = temp;
        }

        // If we represent each right step by R
        // and each down step by D
        // then the number of unique paths from (0, 0) to (m, n)
        // is the number of permutations of m-1 R's and n-1 D's
        // which is (m - 1 + n - 1)! / ((m - 1)! * (n - 1)!)
        // Eg: 3 R and 2 D
        // # ways = (3 + 2)! / (3! * 2!) = 20

        // Make m as m - 1
        // Make n as n - 1
        m--;
        n--;

        // So now we have to compute (m + n)!/(m! * n!)
        // as we decremented m and n
        // = (m+n * (m+n-1) * (m+n-2) * ... m times ...) / m!
        long result = 1;
        for (int i = 0; i < m; i++) {
            result *= (m + n - i);
            result /= (i + 1);
        }
        return (int) result;
    }

    // DP solution
    private int solution2(int m, int n) {
        int[][] dp = new int[m][n];

        // Fill the first row and the first column with 1s
        // as only one way to reach any cell in the first row
        // and the first column
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // dp[i][j] represents the number of unique paths
        // to reach (i, j)
        // Recurrence relation:
        // dp[i][j] = dp[i-1][j] + dp[i][j-1]
        // that is because we can reach (i, j) from (i-1, j) or (i, j-1)
        // so the number paths get added up
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        // Return the number of unique paths
        return dp[m - 1][n - 1];
    }

    public int uniquePaths(int m, int n) {
        return solution1(m, n);
    }
}