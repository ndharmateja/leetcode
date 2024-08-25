public class Solution53 {
    public int maxSubArray(int[] nums) {
        return solution1(nums);
    }

    // O(n^2) time
    // Brute Force
    private int solution1(int[] nums) {
        int[] runningSums = new int[nums.length];
        int sum = 0;
        for (int i = 0; i < runningSums.length; i++) {
            runningSums[i] = sum + nums[i];
            sum += nums[i];
        }
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < runningSums.length; i++) {
            if (runningSums[i] > max) {
                max = runningSums[i];
            }
        }
        for (int i = 0; i < runningSums.length; i++) {
            for (int j = i + 1; j < runningSums.length; j++) {
                if (runningSums[j] - runningSums[i] > max) {
                    max = runningSums[j] - runningSums[i];
                }
            }
        }

        return max;
    }
}