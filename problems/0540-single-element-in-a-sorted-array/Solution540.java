class Solution540 {
    // O(n) time and O(1) space solution
    // Linear search
    public int solution1(int[] nums, int low, int high) {
        int n = nums.length;
        if (n == 1)
            return nums[0];
        if (nums[0] != nums[1])
            return nums[0];
        if (nums[n - 1] != nums[n - 2])
            return nums[n - 1];
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] != nums[i - 1] && nums[i] != nums[i + 1])
                return nums[i];
        }

        // We won't reach here as there is a valid solution
        return -1;
    }

    public int singleNonDuplicate(int[] nums) {
        return solution1(nums, 0, nums.length - 1);
    }
}