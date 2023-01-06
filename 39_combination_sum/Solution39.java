import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution {
    private void backtrack(Set<List<Integer>> output, int[] candidates, int target, int currSum,
            List<Integer> currList) {
        if (currSum > target) {
            return;
        }
        if (currSum == target) {
            List<Integer> list = new ArrayList<>(currList);
            Collections.sort(list);
            output.add(list);
            return;
        }
        for (int candidate : candidates) {
            currList.add(candidate);
            backtrack(output, candidates, target, currSum + candidate, currList);
            currList.remove(currList.size() - 1);
        }
    }

    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        Set<List<Integer>> output = new HashSet<>();
        backtrack(output, candidates, target, target, new ArrayList<>());
        return new ArrayList<>(output);
    }
}