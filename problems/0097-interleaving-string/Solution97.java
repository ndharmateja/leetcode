import java.util.HashMap;

@SuppressWarnings("unused")
public class Solution97 {
    private String s1;
    private String s2;
    private String s3;
    private int m;
    private int n;

    public boolean isInterleave(String s1, String s2, String s3) {
        return solution1(s1, s2, s3);
    }

    // O(m * n) time where m - s1.length() and n - s2.length()
    // O(m * n) space because of the dp 2d array
    // Reference: https://youtu.be/3Rw3p9LrgvE?t=253
    // Bottom up approach
    private boolean solution1(String s1, String s2, String s3) {
        // dp[i][j] tells us if the strings s1[i..m-1] and s2[j..n-1]
        // form a valid interleaving s3[i+j..m+n-1]
        int m = s1.length();
        int n = s2.length();
        boolean[][] dp = new boolean[m + 1][n + 1];

        // Empty strings will always interleave to form another empty string
        dp[m][n] = true;

        // Fill the last column
        for (int i = m - 1; i >= 0; i--) {
            dp[i][n] = (s1.charAt(i) == s3.charAt(i + n)) && dp[i + 1][n];
        }

        // Fill the last row
        for (int j = n - 1; j >= 0; j--) {
            dp[m][j] = (s2.charAt(j) == s3.charAt(m + j)) && dp[m][j + 1];
        }

        // Fill the remaining array starting from the last row to the first
        // In each row, go from right to left
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                dp[i][j] = (s1.charAt(i) == s3.charAt(i + j) && dp[i + 1][j])
                        || (s2.charAt(j) == s3.charAt(i + j) && dp[i][j + 1]);
            }
        }

        return dp[0][0];
    }

    // O(m * n) time where m - s1.length() and n - s2.length()
    // Reference: https://youtu.be/3Rw3p9LrgvE?t=253
    private boolean solution2(String s1, String s2, String s3) {
        // If the number of chars in s1 and s2 don't add up to s3's
        // we can return false
        if (s1.length() + s2.length() != s3.length())
            return false;

        this.s1 = s1;
        this.s2 = s2;
        this.s3 = s3;
        this.m = s1.length();
        this.n = s2.length();

        return solution2(0, 0, new HashMap<>());
    }

    // This is a recursive function
    // solution2(i, j) tells us if the strings s1[i..m-1] and s2[j..n-1]
    // form a valid interleaving s3[i+j..m+n-1]
    // Memoization is done with the hashmap memo
    private boolean solution2(int i, int j, HashMap<Integer, Boolean> memo) {
        // If the memo already contains the solution, we return it
        // 'index' is a unique encoding for (i, j)
        // (0, 0) - 0, (0, 1) - 1, ..., (0, n) - n
        // (1, 0) - n+1, (1, 2) - n+2, ..., (1, n) - (n+1)+1
        // ...
        // (m, 0) - m(n+1)+0, ..., (m, n) - m(n+1)+n
        int index = getIndex(i, j);
        if (memo.containsKey(index))
            return memo.get(index);

        // Base case
        // 2 empty strings will always interleave to form another empty string
        if (i == this.m && j == this.n) {
            memo.put(index, true);
            return true;
        }

        // If the s1[i] matches the s3[i+j]
        // we can remove it and check the interleaving between s1[i+1..m-1] and
        // s2[j..n-1] to form s3[i+j+1..m+n-1]
        if (i < this.m && s1.charAt(i) == s3.charAt(i + j) && solution2(i + 1, j, memo)) {
            memo.put(index, true);
            return true;
        }

        // If the s2[j] matches the s3[i+j]
        // we can remove it and check the interleaving between s1[i..m-1] and
        // s2[j+1..n-1] to form s3[i+j+1..m+n-1]
        if (j < this.n && s2.charAt(j) == s3.charAt(i + j) && solution2(i, j + 1, memo)) {
            memo.put(index, true);
            return true;
        }

        // If we reach here it means that it is not a valid interleaving
        // Either (s1[i] != s3[i+j] and s2[j] != s3[i+j]) or the subproblems both
        // returned false
        memo.put(index, false);
        return false;
    }

    private int getIndex(int i, int j) {
        return i * (n + 1) + j;
    }
}
