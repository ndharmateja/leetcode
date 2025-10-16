import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Solution78 {
    private void backtrack(List<List<Integer>> output, int[] nums, Set<Integer> addedSoFar, int maxAddedSoFar,
            List<Integer> currList) {
        // Add the current list to the output
        output.add(new ArrayList<>(currList));

        // If max size is reached then return
        if (currList.size() == nums.length)
            return;

        // Backtracking
        for (int num : nums) {
            // Since we only want sets and not permutations
            // we will only add numbers that are greater than all the ones
            // already in the curr list
            // This will ensure that there are no duplicate sets
            // We will also add numbers that aren't already in the curr list
            if (addedSoFar.contains(num) || num < maxAddedSoFar)
                continue;

            // Add the new number
            addedSoFar.add(num);
            currList.add(num);

            // Backtrack
            backtrack(output, nums, addedSoFar, num, currList);

            // Remove the new number
            addedSoFar.remove(num);
            currList.remove(currList.size() - 1);
        }
    }

    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, nums, new HashSet<>(), Integer.MIN_VALUE, new ArrayList<>());
        return output;
    }

    public static void main(String[] args) {
        System.out.println(new Solution78().subsets(new int[] { 1, 2, 3 }));
    }
}
