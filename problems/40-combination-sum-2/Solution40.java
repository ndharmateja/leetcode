import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution40 {
    private void backtrack(List<List<Integer>> output, List<Integer> currList, int[] nums, int maxIndex, int currSum,
            int target, Set<String> doneSet) {
        // TODO: Add comments and improve time
        if (doneSet.contains(currList.toString()))
            return;

        doneSet.add(currList.toString());

        // since only positive numbers are involved
        // once curr sum exceeds target we don't have to look along
        // this path anymore
        if (currSum > target)
            return;

        // If curr sum matches target
        // we found a combination
        // so we add it to the output and return
        if (currSum == target) {
            output.add(List.copyOf(currList));
            return;
        }

        // Since we want only unique combinations
        // we don't want to get both [2, 2, 3] and [2, 3, 2] for sum 7
        // So we always get combinations in ascending order
        // Initially we sort nums to make it easier to do that
        // In every call of backtrack, we have a maxIndex which is the max index
        // of any number used in the combination so far
        // so we can only look for numbers at >= maxIndex because new numbers
        // in the combination can only be >= max value in the curr list
        //
        // We could have also stored the maxSoFar int value
        // for each call and loop through all the nums in nums array
        // and skip smaller numbers than maxSoFar
        // We can have a shorter for loop using maxIndex
        for (int i = maxIndex + 1; i < nums.length; i++) {
            int num = nums[i];
            currList.add(num);
            backtrack(output, currList, nums, i, currSum + num, target, doneSet);
            currList.remove(currList.size() - 1);
        }

    }

    public List<List<Integer>> combinationSum2(int[] nums, int target) {
        // Sort the nums array - not necessary if nums is already in sorted order
        Arrays.sort(nums);

        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, new ArrayList<>(), nums, -1, 0, target, new HashSet<>());
        return output;
    }

    public static void main(String[] args) {
        System.out.println(new Solution40().combinationSum2(new int[] { 10, 1, 2, 7, 6, 1, 5 }, 8));
    }
}