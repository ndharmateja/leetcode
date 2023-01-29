import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution1 {

    // O(n^2) time - Brute Force
    private int[] solution1(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target)
                    return new int[] { i, j };
            }
        }
        return null;
    }

    // O(n) time - using HashMap
    // Store each value and its index in the hash map as
    // we iterate
    // If the complement value exists in the map
    // we return the indices
    private int[] solution2(int[] nums, int target) {
        Map<Integer, Integer> numIndexes = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int num = nums[i];
            int diff = target - num;

            if (numIndexes.containsKey(diff)) {
                return new int[] { numIndexes.get(diff), i };
            }

            numIndexes.put(num, i);
        }
        return null;
    }

    public int[] twoSum(int[] nums, int target) {
        return solution2(nums, target);
    }
}