import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution46 {
    private void backtrack(List<List<Integer>> output, int[] nums, Set<Integer> addedSoFar, List<Integer> currList) {
        if (addedSoFar.size() == nums.length) {
            output.add(List.copyOf(currList));
            return;
        }
        for (int num : nums) {
            if (addedSoFar.contains(num)) {
                continue;
            }
            addedSoFar.add(num);
            currList.add(num);
            backtrack(output, nums, addedSoFar, currList);
            addedSoFar.remove(num);
            currList.remove(currList.size() - 1);
        }
    }

    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, nums, new HashSet<>(), new ArrayList<>());
        return output;
    }
}