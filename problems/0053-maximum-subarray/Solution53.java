@SuppressWarnings("unused")
public class Solution53 {
    public int maxSubArray(int[] nums) {
        return solution3(nums);
    }

    // O(n^2) time
    // Brute Force
    private int solution1(int[] nums) {
        int[] runningSums = new int[nums.length];
        int sum = 0;
        for (int i = 0; i < runningSums.length; i++) {
            runningSums[i] = sum + nums[i];
            sum += nums[i];
        }
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < runningSums.length; i++) {
            if (runningSums[i] > max) {
                max = runningSums[i];
            }
        }
        for (int i = 0; i < runningSums.length; i++) {
            for (int j = i + 1; j < runningSums.length; j++) {
                if (runningSums[j] - runningSums[i] > max) {
                    max = runningSums[j] - runningSums[i];
                }
            }
        }

        return max;
    }

    // O(n) time and O(n) space solution
    // Bottom Up DP approach
    private int solution2(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];

        // dp[i] - stores the maximum sum of a subarray ending
        // exactly at nums[i]

        // Base case:
        // dp[0] = nums[0]
        dp[0] = nums[0];
        int maxSoFar = dp[0];

        // Recurrence:
        // dp[i] = nums[i] + (dp[i-1] < 0 ? 0 : dp[i-1])
        //
        // Since dp[i] represents the max sum of a subarray *including* nums[i],
        // dp[i] has to include the value of nums[i]
        // If the max sum of a subarray ending at nums[i-1] is negative
        // then including that sum in dp[i] only reduces the value, so we
        // don't include it
        // If it is non-negative, then we can add that to our current
        // nums[i] as adding dp[i-1] won't decrease the sum

        // As dp[i] only depends upon dp[i-1] we can fill the dp array
        // from left to right

        // The result is the max value among all the values in the dp array
        // as the subarray can end anywhere
        for (int i = 1; i < n; i++) {
            dp[i] = nums[i] + (dp[i - 1] < 0 ? 0 : dp[i - 1]);
            maxSoFar = dp[i] > maxSoFar ? dp[i] : maxSoFar;
        }
        return maxSoFar;
    }

    // O(n) time and O(1) space solution
    // Space optimized version of solution 2 - read that first
    private int solution3(int[] nums) {
        // As we only need the i-1 th subproblem's solution
        // we can get away with one variable instead of a whole array
        int curr = nums[0];
        int maxSoFar = curr;
        for (int i = 1; i < nums.length; i++) {
            curr = nums[i] + (curr < 0 ? 0 : curr);
            maxSoFar = curr > maxSoFar ? curr : maxSoFar;
        }
        return maxSoFar;

    }
}