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

    // O(n logn) time and O(logn) space (max depth of the recursive stack) solution
    // Recursive Divide and Conquer solution
    // Recurrence relation for runtime:
    // T(n) = 2T(n/2) + O(n)
    // => O(n logn) running time using Master's theorem
    public int solution4(int[] nums) {
        return solution4(nums, 0, nums.length - 1);
    }

    // This function recursively computes the max subarray sum of the array 'nums'
    // in the range of l to h (both inclusive)
    private int solution4(int[] nums, int l, int h) {
        // Base case
        // If only one element, then max sum would be the element itself
        // as the subarray has to be non-empty according the definition provided
        // So we take the element even if it is negative
        if (l == h)
            return nums[l];
        int m = (l + h) / 2;

        // Find the max sum of a subarray completely contained in the left half
        int maxLeftSubArraySum = solution4(nums, l, m);

        // Find the max sum of a subarray completely contained in the right half
        int maxRightSubArraySum = solution4(nums, m + 1, h);

        // Find the max subarray sum of a subarray that crosses both halves
        // That means that a part of this subarray would be the suffix of the left half
        // and the remaining part of this subarray would be the prefix of the right half
        // To maximize the this sum, we maximize the suffix and the prefix
        // So we take the max among all the suffixes from the left half
        // and the max among all the prefixes from the right half
        // and their sum would be the max sum of a subarray that crosses both halves
        int maxCrossArraySum = maxSuffixSum(nums, l, m) + maxPrefixSum(nums, m + 1, h);

        // Take the max among these 3 sums
        return max(maxLeftSubArraySum, maxRightSubArraySum, maxCrossArraySum);
    }

    private int max(int a, int b) {
        return a > b ? a : b;
    }

    private int max(int a, int b, int c) {
        return max(max(a, b), c);
    }

    private int maxSuffixSum(int[] nums, int l, int end) {
        int maxSum = nums[end];
        int currSum = nums[end];
        for (int i = end - 1; i >= l; i--) {
            currSum += nums[i];
            if (currSum > maxSum)
                maxSum = currSum;
        }
        return maxSum;
    }

    private int maxPrefixSum(int[] nums, int start, int h) {
        int maxSum = nums[start];
        int currSum = nums[start];
        for (int i = start + 1; i <= h; i++) {
            currSum += nums[i];
            if (currSum > maxSum)
                maxSum = currSum;
        }
        return maxSum;
    }
}