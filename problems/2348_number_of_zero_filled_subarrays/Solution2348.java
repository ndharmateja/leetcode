class Solution2348 {
    /**
     * if zeroSubarraySize is 4
     * The total number of zero subarrays are
     * 1 [0, 0, 0, 0] + 2 [0, 0, 0] + 3 [0, 0] + 4 [0] = 10
     * 
     * @param zeroSubarraySize
     * @return
     */
    private long getZeroSubarraysCount(long zeroSubarraySize) {
        return zeroSubarraySize * (zeroSubarraySize + 1) / 2;
    }

    public long zeroFilledSubarray(int[] nums) {
        long count = 0;

        long currZeroSubarraySize = 0;
        for (int num : nums) {
            // reached the end of curr zeroes subarray
            if (num != 0 && currZeroSubarraySize > 0) {
                count += getZeroSubarraysCount(currZeroSubarraySize);
                currZeroSubarraySize = 0;
            }

            // If we encounter zero, we increment curr zero subarray size
            else if (num == 0) {
                currZeroSubarraySize++;
            }
        }

        // Get the count of the zero subarray at the end (if any)
        count += getZeroSubarraysCount(currZeroSubarraySize);

        return count;
    }
}