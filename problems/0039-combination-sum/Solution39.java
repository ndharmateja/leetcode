import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("unused")
class Solution39 {
    private void backtrack(List<List<Integer>> output, List<Integer> currList, int[] nums, int maxIndex, int currSum,
            int target) {
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
        // So we always get combinations in ascending order of indexes in nums array
        // In every call of backtrack, we have a maxIndex which is the max index
        // of any number used in the combination so far
        // so we can only look for numbers at >= maxIndex
        // since we only use ascending order of indexes (from original array)
        // for unique combinations
        for (int i = maxIndex; i < nums.length; i++) {
            int num = nums[i];
            currList.add(num);
            backtrack(output, currList, nums, i, currSum + num, target);
            currList.remove(currList.size() - 1);
        }
    }

    private List<List<Integer>> solution1(int[] nums, int target) {
        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, new ArrayList<>(), nums, 0, 0, target);
        return output;
    }

    private void dfs(int[] nums, int target, int i, int currSum, List<Integer> currList, List<List<Integer>> output) {
        // If the currSum crosses the target, then there is no point continuing
        // as all the numbers are positive
        if (currSum > target)
            return;

        // If targer sum is found, we can add this sequence to our result and exit
        if (currSum == target) {
            output.add(new ArrayList<>(currList));
            return;
        }

        // If we reach the end, we don't need to do anything
        // so we can simply return
        if (i == nums.length)
            return;

        // Two options pick the current one or don't pick the current one
        // 1. If we pick the current one, we add that to the current sum
        // and the current list to track the sequence and then
        // we call the dfs starting from *the same element* again
        // as each element can be picked multiple times
        // That is why we call dfs again from 'i' instead of 'i+1'
        currList.add(nums[i]);
        dfs(nums, target, i, currSum + nums[i], currList, output);
        currList.remove(currList.size() - 1);

        // 2. If we don't pick the current element, we call dfs starting from the
        // next element
        dfs(nums, target, i + 1, currSum, currList, output);
    }

    private List<List<Integer>> solution2(int[] nums, int target) {
        List<List<Integer>> output = new ArrayList<>();
        dfs(nums, target, 0, 0, new ArrayList<>(), output);
        return output;
    }

    public List<List<Integer>> combinationSum(int[] nums, int target) {
        return solution2(nums, target);
    }

    public static void main(String[] args) {
        System.out.println(new Solution39().combinationSum(new int[] { 2, 3, 6, 7 }, 7));
    }
}