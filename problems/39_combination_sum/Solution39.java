import java.util.ArrayList;
import java.util.List;

class Solution39 {
    private void backtrack(List<List<Integer>> output, List<Integer> currList, int[] nums, int maxSoFar, int currSum,
            int target) {
        if (currSum > target)
            return;
        if (currSum == target) {
            output.add(List.copyOf(currList));
            return;
        }
        for (int num : nums) {
            if (num < maxSoFar)
                continue;
            currList.add(num);
            backtrack(output, currList, nums, num, currSum + num, target);
            currList.remove(currList.size() - 1);
        }
    }

    public List<List<Integer>> combinationSum(int[] nums, int target) {
        List<List<Integer>> output = new ArrayList<>();
        backtrack(output, new ArrayList<>(), nums, Integer.MIN_VALUE, 0, target);
        return output;
    }

    public static void main(String[] args) {
        System.out.println(new Solution39().combinationSum(new int[] { 2, 3, 6, 7 }, 7));
    }
}