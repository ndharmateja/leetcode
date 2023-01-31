class Solution1991 {
    public int findMiddleIndex(int[] nums) {
        if (nums.length == 1)
            return 0;

        int[] prefixSums = new int[nums.length];
        int[] postfixSums = new int[nums.length];

        prefixSums[0] = nums[0];
        for (int i = 1; i < nums.length; i++) {
            prefixSums[i] = prefixSums[i - 1] + nums[i];
        }

        postfixSums[nums.length - 1] = nums[nums.length - 1];
        for (int i = nums.length - 2; i >= 0; i--) {
            postfixSums[i] = postfixSums[i + 1] + nums[i];
        }

        if (postfixSums[1] == 0)
            return 0;
        for (int i = 1; i < nums.length - 1; i++) {
            if (prefixSums[i - 1] == postfixSums[i + 1])
                return i;
        }
        if (prefixSums[nums.length - 2] == 0)
            return nums.length - 1;

        return -1;
    }
}