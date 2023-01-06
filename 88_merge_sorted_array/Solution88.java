class Solution88 {
    // [1, 2, 3, 4, 0, 0] will become [0, 0, 1, 2, 3, 4]
    private void moveZeroesToStart(int[] nums, int numZeroes) {
        if (numZeroes == 0)
            return;

        int numNonZeroes = nums.length - numZeroes;

        // From right, move each non-zero value to end
        // Run loop numNonZeroes number of times
        for (int i = 0; i < numNonZeroes; i++) {
            nums[nums.length - 1 - i] = nums[nums.length - 1 - i - numZeroes];
        }

        // Make first numZeroes values to 0
        for (int i = 0; i < numZeroes; i++) {
            nums[i] = 0;
        }
    }

    // O(n) time and O(1) space
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        this.moveZeroesToStart(nums1, n); // because there are 'n' zeroes at the end

        // nums1 = [0, 0, 0, 0, 1, 2, 3]
        // nums2 = [2, 5, 6, 7]
        // i starts from index where '1' is there
        // j starts from 0
        // k is the index that tracks the index pos
        // where we need to insert the next smallest element
        // in nums1
        int i = n;
        int j = 0;
        int k = 0;
        while (i < nums1.length && j < nums2.length) {
            if (nums1[i] <= nums2[j]) {
                nums1[k++] = nums1[i++];
            } else {
                nums1[k++] = nums1[j++];
            }
        }
        while (i < nums1.length) {
            nums1[k++] = nums1[i++];
        }
        while (j < nums2.length) {
            nums1[k++] = nums1[j++];
        }
    }
}
