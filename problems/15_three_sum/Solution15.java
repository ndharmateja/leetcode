import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@SuppressWarnings("unused")
class Solution15 {

    // O(n^3) solution - Brute Force
    private List<List<Integer>> solution1(int[] nums) {
        Set<List<Integer>> output = new HashSet<>();
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                for (int k = j + 1; k < nums.length; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        List<Integer> list = Arrays.asList(nums[i], nums[j], nums[k]);
                        Collections.sort(list);
                        output.add(list);
                    }
                }
            }
        }
        return new ArrayList<>(output);
    }

    // O(n^2) time
    // Reference: https://youtu.be/jzZsG8n2R9A
    // Method: (say finding all unique [a, b, c] such that a + b + c = 0)
    // 1. sort the array
    // 2. For each number (a) in the array, find the all the two sums
    // (with target as "0 - number") for the right sub array.
    // 3. We avoid duplicates for 'a' by skipping numbers (in the outer loop) that
    // is same as the previous number
    // 4. In the inner loop we avoid duplicates for 'b', by moving "left"
    // pointer across all the duplicate found "left" index values (after
    // finding an appropriate two sum)
    // 5. If we avoid duplicates for 'a' and 'b', then all duplicates are avoided
    private List<List<Integer>> solution2(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> output = new ArrayList<>();
        for (int i = 0; i < nums.length - 2; i++) {
            // to avoid duplicates for 'a'
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = nums.length - 1;
            int num = nums[i];
            int targetTwoSum = -num;

            while (left < right) {
                if (nums[left] + nums[right] < targetTwoSum)
                    left++;
                else if (nums[left] + nums[right] > targetTwoSum)
                    right--;
                else {
                    output.add(Arrays.asList(num, nums[left], nums[right]));
                    left++;
                    // to avoid duplicates for 'b'
                    while (nums[left] == nums[left - 1] && left < right) {
                        left++;
                    }
                }
            }

        }
        return output;
    }

    public List<List<Integer>> threeSum(int[] nums) {
        return solution2(nums);
    }

}