import java.util.ArrayList;
import java.util.List;

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
            output.add(List.copyOf(currList));
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

    public List<List<Integer>> combinationSum(int[] nums, int target) {
        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, new ArrayList<>(), nums, 0, 0, target);
        return output;
    }

    public static void main(String[] args) {
        System.out.println(new Solution39().combinationSum(new int[] { 2, 3, 6, 7 }, 7));
    }
}