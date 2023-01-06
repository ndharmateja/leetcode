class Solution977 {
    // O(n) time and O(n) space
    public int[] sortedSquares(int[] nums) {
        // Find index of first non-negative number
        int r = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] >= 0)
                break;
            r++;
        }

        // 'l' tracks the last negative number
        int l = r - 1;

        // Each iteration take the values between l and r indices
        // with smaller absolute value and add it to squares array
        // Essentially we start at the center of negative and positive
        // and keep moving out
        int i = 0;
        int[] squares = new int[nums.length];
        while (l >= 0 && r < nums.length) {
            if (-nums[l] <= nums[r])
                squares[i++] = nums[l] * nums[l--];
            else
                squares[i++] = nums[r] * nums[r++];
        }
        while (l >= 0)
            squares[i++] = nums[l] * nums[l--];
        while (r < nums.length)
            squares[i++] = nums[r] * nums[r++];

        return squares;
    }
}