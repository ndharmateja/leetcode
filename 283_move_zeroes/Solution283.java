class Solution283 {
    // O(n) time and O(1) space solution
    // For each element from the right, start populating
    // from the start of the array with the non-zero values
    // At the end make all the remaining values as zero
    public void moveZeroes(int[] nums) {
        int k = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                nums[k++] = nums[i];
            }
        }
        for (int i = k; i <= nums.length; i++) {
            nums[i] = 0;
        }
    }
}