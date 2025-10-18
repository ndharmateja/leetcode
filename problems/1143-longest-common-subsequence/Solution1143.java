@SuppressWarnings("unused")
class Solution1143 {
    public int longestCommonSubsequence(String s1, String s2) {
        return solution1(s1, s2);
    }

    // O(mn) time and O(mn) space
    // Bottom up DP approach
    private int solution1(String s1, String s2) {
        // Initialize DP array
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];

        // DP array
        // dp[i][j] - represents the length of the lcs between
        // s1[i:] and s2[j:]

        // Base cases
        // dp[m][:] = 0 (last row is 0)
        // dp[:][n] = 0 (last col is 0)
        // As the lcs length between an empty string and anything is 0
        //
        // Java sidenote: by default, the int arrays are initialized to 0s
        // so these loops aren't strictly necessary
        // for (int j = 0; j < n + 1; j++) { dp[m][j] = 0; }
        // for (int i = 0; i < m + 1; i++) { dp[i][n] = 0; }

        // DP recurrence relation:
        // dp[i][j] = (s1[i] == s2[j]) ? 1 + dp[i+1][j+1]
        // ........................... : max(dp[i+1][j], dp[i][j+1])
        // Explanation:
        // 1. If the characters s1[i] and s2[j] are same (say 'c'), then the
        // length of the lcs between s1[i:] and s2[j:] is 1 more than
        // the length of the lcs between s1[i+1:] and s2[j+1:] as we can
        // get the larger lcs by adding the char 'c' to the smaller lcs
        // 2. If they don't match, then the length of the lcs would be the max between
        // either removing the ith char in s1 or by removing the jth char in s2
        // which is given by max(dp[i+1][j], dp[i][j+1])
        //
        // We fill the remaining DP array starting from the m-1th row to the 0th row
        // and going from n-1th col to the 0th col in each row. This works as each
        // DP value depends only on the values to the right and bottom or bottom right
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                dp[i][j] = s1.charAt(i) == s2.charAt(j)
                        ? 1 + dp[i + 1][j + 1]
                        : max(dp[i + 1][j], dp[i][j + 1]);

        // The answer is contained in dp[0][0] as it represents the length of the lcs
        // between s1[0:] and s2[0:] which is exactly what we need
        return dp[0][0];
    }

    private int max(int a, int b) {
        return a > b ? a : b;
    }

    public static void main(String[] args) {
        Solution1143 s = new Solution1143();
        System.out.println(s.longestCommonSubsequence("ABCDE", "ACE"));
    }
}