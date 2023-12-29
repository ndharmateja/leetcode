public class Solution221 {
    private static int min(int a, int b, int c) {
        return Math.min(Math.min(a, b), c);
    }

    // O(n^2) time and O(n^2) space solution
    public int maximalSquare(char[][] a) {
        // Base case
        int m = a.length;
        int n = a[0].length;
        if (m == 1 && n == 1)
            return a[0][0] == '0' ? 0 : 1;

        // DP:
        // 1. Each value at (r, c) will signify the size of the
        // max square submatrix that ends at (r, c)
        // 2. For first row and first col, the values will be
        // the original array values, as if the value is 1
        // then the max square subsize ending at that cell is 1
        // and if it is 0, the dp value is also going to be 0
        // 3. dp[r][c] = 0 if a[r][c] = 0
        // 4. dp[r][c] = 1 + min(dp[r - 1][c - 1], dp[r - 1][c], dp[r][c - 1])
        int max = 0;
        int[][] dp = new int[m][n];
        for (int r = 0; r < m; r++) {
            dp[r][0] = a[r][0] == '0' ? 0 : 1;
            max = Math.max(max, dp[r][0]);
        }
        for (int c = 0; c < n; c++) {
            dp[0][c] = a[0][c] == '0' ? 0 : 1;
            max = Math.max(max, dp[0][c]);
        }
        for (int r = 1; r < m; r++) {
            for (int c = 1; c < n; c++) {
                if (a[r][c] == '1') {
                    dp[r][c] = 1 + min(dp[r - 1][c - 1], dp[r - 1][c], dp[r][c - 1]);

                    // Update max
                    max = Math.max(max, dp[r][c]);
                }

            }
        }

        // Return area
        return max * max;
    }
}