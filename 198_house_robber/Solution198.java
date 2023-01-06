class Solution198 {
    // O(n) time and O(1) space
    // Reference: https://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/
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
    public int rob(int[] nums) {
        int including = 0;
        int excluding = 0;

        for (int num : nums) {
            int prevMaxValue = Math.max(including, excluding);
            including = excluding + num;
            excluding = prevMaxValue;
        }

        return Math.max(including, excluding);
    }
}