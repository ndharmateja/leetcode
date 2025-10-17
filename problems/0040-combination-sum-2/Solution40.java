import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@SuppressWarnings("unused")
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
            output.add(new ArrayList<>(currList));
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

    private List<List<Integer>> solution1(int[] nums, int target) {
        // Sort the nums array - not necessary if nums is already in sorted order
        Arrays.sort(nums);

        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, new ArrayList<>(), nums, -1, 0, target, new HashSet<>());
        return output;
    }

    private void dfs(int[] nums, int target, Set<List<Integer>> set, int index, List<Integer> currList, int currSum) {
        // If sum of the combination so far has already exceeded the target
        // no point in exploring further as all the numbers are positive
        if (currSum > target)
            return;

        // If we found a combination (a subsequence) that adds up to the target sum
        // we add that list to the set
        // Since the nums array is sorted, duplicate combinations will not be added
        // more than once as they will be same because of the sorting
        if (currSum == target) {
            set.add(new ArrayList<>(currList));
            return;
        }

        // Base case
        // If we reach the end of the list, we can return
        if (index == nums.length)
            return;

        // Explore further by choosing current element
        // We use 'index + 1' because we are only choosing each element only once
        // unlike the combination sum 1 problem where we were allowed to choose
        // each element more than once
        // After the exploration is done, we remove the current element
        // from the combination (subsequence)
        currList.add(nums[index]);
        dfs(nums, target, set, index + 1, currList, currSum + nums[index]);
        currList.remove(currList.size() - 1);

        // Backtrack by not choosing current element
        dfs(nums, target, set, index + 1, currList, currSum);
    }

    private List<List<Integer>> solution2(int[] nums, int target) {
        Arrays.sort(nums);
        Set<List<Integer>> result = new HashSet<>();
        dfs(nums, target, result, 0, new ArrayList<>(), 0);
        return new ArrayList<>(result);
    }

    public List<List<Integer>> combinationSum2(int[] nums, int target) {
        return solution2(nums, target);
    }
}