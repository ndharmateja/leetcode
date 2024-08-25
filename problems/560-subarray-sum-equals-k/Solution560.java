import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution560 {
    public int subarraySum(int[] nums, int k) {
        return solution2(nums, k);
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

    // O(n) time and O(n) space solution
    // Reference: https://youtu.be/fFVZt-6sgyo
    private int solution2(int[] nums, int k) {
        // Hash map for prefix sum counts
        Map<Integer, Integer> prefixSumCounts = new HashMap<>();

        // We add a count of '1' for '0'
        // to account for the fact if the currPrefixSum itself
        // is equal to 'k', then we will have a value of '1'
        // for (currPrefixSum - k = 0)
        prefixSumCounts.put(0, 1);

        // Count variable for storing total counts
        int count = 0;
        int currPrefixSum = 0;

        // Compute prefix sums and store them in nums itself
        for (int num : nums) {
            // Get count of all complement prefix sums (k - currPrefixSum)
            // from map and add to count
            // Since a subarray sum is the difference in the prefix sums
            currPrefixSum += num;
            int complementSum = currPrefixSum - k;
            count += prefixSumCounts.getOrDefault(complementSum, 0);

            // Put current prefix sum in the map
            prefixSumCounts.put(currPrefixSum, prefixSumCounts.getOrDefault(currPrefixSum, 0) + 1);
        }

        return count;
    }
}