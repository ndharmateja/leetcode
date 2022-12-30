import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution {
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

    public List<List<Integer>> threeSum(int[] nums) {
        return solution1(nums);
    }
}