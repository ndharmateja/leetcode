public class Solution63 {
    private int solution1(int[][] obstacleGrid) {
        // If the (0, 0) element itself consists of the robot
        // then the number of paths would be 0
        if (obstacleGrid[0][0] == 1)
            return 0;

        int m = obstacleGrid.length;
        int n = obstacleGrid[0].length;
        int[][] dp = new int[m][n];

        // Fill the first row with 1s
        // as there is only one way to reach each element in the first row
        // unless there is an obstacle in which case
        // the element with the obstacle and all the elements next to it will
        // have a 0
        dp[0][0] = 1;
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j] == 1)
                dp[0][j] = 0;
            else
                dp[0][j] = dp[0][j - 1];
        }

        // Same with the first column
        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0] == 1)
                dp[i][0] = 0;
            else
                dp[i][0] = dp[i - 1][0];
        }

        // Fill all the remaining elements
        // starting from first row (not the 0th) to the last row
        // and fill elements from left to right in each row
        // If the element contains an obstacle, then the number of
        // ways to reach that cell becomes 0
        // otherwise it is the sum of the element above and element left
        // dp[i][j] = (obstacleGrid[i][j] == 1) ? 0 : dp[i - 1][j] + dp[i][j - 1]
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = (obstacleGrid[i][j] == 1)
                        ? 0
                        : dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    public int uniquePathsWithObstacles(int[][] obstacleGrid) {
        return solution1(obstacleGrid);
    }
}
