@SuppressWarnings("unused")
class Solution238 {
    // O(n) time and O(1) space
    // Reference: https://youtu.be/bNvIQI2wAjk?t=290
    private int[] solution2(int[] nums) {
        // Compute prefixes and store in output array (to one index on right)
        int pre = 1;
        int[] output = new int[nums.length];
        output[0] = 1;
        for (int i = 0; i < nums.length - 1; i++) {
            pre *= nums[i];
            output[i + 1] = pre;
        }

        // Compute postfix step by step and multiply with elements in output array
        int post = 1;
        for (int i = output.length - 1; i > 0; i--) {
            post *= nums[i];
            output[i - 1] *= post;
        }

        // Return output
        return output;
    }

    // O(n) time and O(n) space
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
        return solution2(nums);
    }
}