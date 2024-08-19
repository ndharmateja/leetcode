import java.util.ArrayList;
import java.util.List;

class Solution46 {
    List<List<Integer>> output = new ArrayList<>();
    List<Integer> currList = new ArrayList<>();

    private void backtrack(int[] nums, boolean[] added) {
        // If the permutation size reaches its limit
        // we can add it to the list of permutations
        if (currList.size() == nums.length) {
            output.add(new ArrayList<>(currList));
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            // If the current number is already added, we don't need to add it
            int num = nums[i];
            if (added[i]) {
                continue;
            }

            // Else add the current number to the permutation
            // Backtrack
            // Remove the number
            added[i] = true;
            currList.add(num);
            backtrack(nums, added);
            added[i] = false;
            currList.remove(currList.size() - 1);
        }
    }

    public List<List<Integer>> permute(int[] nums) {
        backtrack(nums, new boolean[nums.length]);
        return output;
    }
}