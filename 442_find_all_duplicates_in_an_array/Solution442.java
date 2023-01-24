import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution442 {
    public List<Integer> findDuplicates(int[] nums) {
        return solution1(nums);
    }

    // O(n) time and O(n) space solution
    private List<Integer> solution1(int[] nums) {
        List<Integer> output = new ArrayList<>();
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            if (set.contains(num)) {
                output.add(num);
                set.remove(num);
            } else {
                set.add(num);
            }
        }
        return output;
    }
}