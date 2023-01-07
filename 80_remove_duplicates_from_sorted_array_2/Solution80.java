class Solution80 {

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int removeDuplicates(int[] nums) {
        // We start from i as 1 because
        // the first two elements are always going to be part
        // of the final array
        int i = 1;
        for (int j = 2; j < nums.length; j++) {
            if (nums[j] > nums[i] || (i > 0 && nums[j] == nums[i] && nums[j] != nums[i - 1])) {
                i++;
                swap(nums, i, j);
            }
        }
        return i + 1;
    }
}