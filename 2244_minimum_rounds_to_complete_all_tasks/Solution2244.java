import java.util.HashMap;
import java.util.Map;

class Solution2244 {
    Map<Integer, Integer> memo = new HashMap<>();

    public Solution2244() {
        memo.put(0, 0);
        memo.put(1, Integer.MAX_VALUE);
        memo.put(2, 1);
        memo.put(3, 1);
    }

    // Calculates the number of min rounds for a given number
    // of tasks with same level using DP
    // We also memoize the values (since only the number of tasks
    // of a certain level matter and not the task itself)
    // For eg, min number of rounds to solve 3 tasks for task 2 or task 4
    // takes the same number of min rounds
    private int getMinimumRounds(int numTasksOfSameLevel) {
        if (!memo.containsKey(numTasksOfSameLevel)) {
            int numRounds = Math.min(
                    getMinimumRounds(numTasksOfSameLevel - 2),
                    getMinimumRounds(numTasksOfSameLevel - 3)) + 1;
            memo.put(numTasksOfSameLevel, numRounds);
        }
        return memo.get(numTasksOfSameLevel);
    }

    public int minimumRounds(int[] tasks) {
        // Get counts of each task
        Map<Integer, Integer> taskCounts = new HashMap<>();
        for (int task : tasks) {
            taskCounts.put(task, taskCounts.getOrDefault(task, 0) + 1);
        }

        // For each task count, get min rounds
        // and add it to our total
        int totalRounds = 0;
        for (int numTasksOfSameLevel : taskCounts.values()) {
            if (numTasksOfSameLevel == 1)
                return -1;
            totalRounds += getMinimumRounds(numTasksOfSameLevel);
        }

        return totalRounds;
    }

    public static void main(String[] args) {
        Solution2244 sol = new Solution2244();
        System.out.println(sol.getMinimumRounds(4));
    }
}