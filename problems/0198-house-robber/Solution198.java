import java.util.HashMap;

@SuppressWarnings("unused")
class Solution198 {
    public int rob(int[] nums) {
        return solution1(nums);
    }

    // O(n) time and O(n) space
    // O(n) space as we are using 2 arrays of size n
    private int solution1(int[] nums) {
        int n = nums.length;
        int[] including = new int[n];
        int[] excluding = new int[n];

        // Until the 0th index, we can only include nums[0]
        // or exclude nums[0]
        including[0] = nums[0];
        excluding[0] = 0;

        for (int i = 1; i < n; i++) {
            // If we include nums[i], we exclude nums[i - 1]
            // so we take the value of excluding[i - 1] and add nums[i]
            including[i] = excluding[i - 1] + nums[i];

            // If we exclude nums[i], we can take the max between
            // including[i - 1] and excluding[i - 1] as we can either include it or not
            excluding[i] = max(including[i - 1], excluding[i - 1]);
        }

        // Return the max between including[n - 1] and excluding[n - 1]
        return max(including[n - 1], excluding[n - 1]);
    }

    // Solution 2 is just a space optimized version of solution 1
    // O(n) time and O(1) space
    // Reference:
    // https://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/
    // Solved using DP
    // At each point we have the max sum so far including
    // and excluding the prev value
    // We compute the values of maxes including and excluding
    // the current value as follows
    // if we include curr => exclude prev
    // => including = excluding + currVal
    // If we exclude curr => we can either exclude or include prev
    // so we take the max
    // => excluding = max(excluding, including)
    private int solution2(int[] nums) {
        int including = 0;
        int excluding = 0;

        for (int num : nums) {
            int prevMaxValue = max(including, excluding);
            including = excluding + num;
            excluding = prevMaxValue;
        }

        return max(including, excluding);
    }

    // O(n) time and O(n) space
    // O(n) space as we are using 1 array of size n
    private int solution3(int[] nums) {
        // Base case: If there is only one house, we can only rob it
        int n = nums.length;
        if (n == 1)
            return nums[0];

        // dp[i] stores the max sum until index i
        int[] dp = new int[n];
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            // If we include nums[i], we exclude nums[i - 1],
            // so we take nums[i] + dp[i - 2]
            // If we exclude nums[i], we take dp[i - 1]
            // That is why we take the max between them
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }

    // O(n) time and O(1) space
    // Solution 4 is just a space optimized version of solution 3
    private int solution4(int[] nums) {
        if (nums.length == 1)
            return nums[0];

        // Stores the max sum of the prev two indices
        int prev_prev = nums[0];
        int prev = max(nums[0], nums[1]);

        for (int i = 2; i < nums.length; i++) {
            // If we include nums[i], we exclude nums[i - 1],
            // so we take nums[i] + prev_prev
            // If we exclude nums[i], we take prev
            // So we take the max between them
            int curr = max(prev, prev_prev + nums[i]);
            prev_prev = prev;
            prev = curr;
        }

        // Return the max sum which is stored in prev at the en
        return prev;
    }

    // O(n) time and O(n) space
    // O(n) space because the recursion stack size can go up to n
    private int solution5(int[] nums) {
        return solution5(nums, nums.length - 1, new HashMap<>());
    }

    // Recursive function for top down DP approach
    private int solution5(int[] nums, int i, HashMap<Integer, Integer> memo) {
        // If the memo contains the value, return it
        if (memo.containsKey(i))
            return memo.get(i);

        // Base cases
        if (i == 0) {
            memo.put(i, nums[0]);
            return nums[0];
        }
        if (i == 1) {
            memo.put(i, max(nums[0], nums[1]));
            return max(nums[0], nums[1]);
        }

        // If we include nums[i], we exclude nums[i - 1],
        // so we take nums[i] + solution5(nums, i - 2, memo)
        // If we exclude nums[i], we take solution5(nums, i - 1, memo)
        // That is why we take the max between them
        int include = nums[i] + solution5(nums, i - 2, memo);
        int exclude = solution5(nums, i - 1, memo);
        memo.put(i, max(include, exclude));

        // Return the max sum
        return memo.get(i);
    }

    private int max(int a, int b) {
        return a > b ? a : b;
    }
}