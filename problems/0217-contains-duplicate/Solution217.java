import java.util.Arrays;
import java.util.HashSet;

@SuppressWarnings("unused")
class Solution217 {
    // O(n) time and O(n) space
    private boolean solution1(int[] nums) {
        HashSet<Integer> set = new HashSet<>();
        for (int num : nums) {
            if (!set.add(num))
                return true;
        }
        return false;
    }

    // O(n log n) time and O(1) space
    private boolean solution2(int[] nums) {
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 1; i++) {
            if (nums[i] == nums[i + 1])
                return true;
        }
        return false;
    }

    // O(n^2) time and O(1) space
    private boolean solution3(int[] nums) {
        for (int i = 0; i < nums.length - 1; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] == nums[j])
                    return true;
            }
        }
        return false;
    }

    public boolean containsDuplicate(int[] nums) {
        return solution1(nums);
    }
}