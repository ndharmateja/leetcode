import java.util.Arrays;

@SuppressWarnings("unused")
class Solution560 {
    public int subarraySum(int[] nums, int k) {
        return solution1(nums, k);
    }

    // O(n^2) time and O(1) space solution
    // Brute Force
    private int solution1(int[] nums, int k) {
        // If first element is equal to 'k'
        // count will be '1' else '0'
        int count = nums[0] == k ? 1 : 0;

        // Calculate all the prefix sums and store them
        // in nums array themselves
        for (int i = 1; i < nums.length; i++) {
            nums[i] += nums[i - 1];
            // If a particular sum is equal to 'k'
            // we increment the count
            // As a prefix sum can be a subarray
            // as we will be looking at only differences
            // in the next section
            if (nums[i] == k) {
                count++;
            }
        }

        // We look at all possible differences in
        // prefix sums to find subarrays with
        // sum equal to 'k'
        for (int i = 0; i < nums.length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] - nums[j] == k)
                    count++;
            }
        }

        return count;
    }
}