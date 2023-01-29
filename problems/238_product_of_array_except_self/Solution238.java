class Solution238 {

    // Time: O(n)
    // Space: O(n)
    private int[] solution1(int[] nums) {
        // 1. Get cumulative products of nums
        // both left to right (prefix) and right to left (postfix)
        // Eg: nums - [1, 2, 3, 4]
        // prefix - [1, 2, 6, 24]
        // postfix - [24, 24, 12, 4]
        int n = nums.length;
        int[] prefix = new int[n];
        int[] postfix = new int[n];

        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * nums[i];
        }
        postfix[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            postfix[i] = postfix[i + 1] * nums[i];
        }

        // 2. In output array, ith element = prefix[i - 1] * postfix[i + 1]
        // Eg: nums - [1, 2, 3, 4]
        // prefix - [1, 2, 6, 24]
        // postfix - [24, 24, 12, 4]
        // output[1] = prefix[0] * postfix[2] = 1 * 12 = 12
        // output[2] = prefix[1] * postfix[3] = 2 * 4 = 8
        int[] output = new int[n];
        output[0] = postfix[1];
        output[n - 1] = prefix[n - 2];
        for (int i = 1; i < n - 1; i++) {
            output[i] = prefix[i - 1] * postfix[i + 1];
        }
        return output;
    }

    public int[] productExceptSelf(int[] nums) {
        return solution1(nums);
    }
}