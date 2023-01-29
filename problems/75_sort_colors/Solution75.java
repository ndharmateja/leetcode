class Solution75 {
    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public void sortColors(int[] nums) {
        int j = 0, k = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 1) {
                swap(nums, k, i);
                k++;
            } else if (nums[i] == 0) {
                swap(nums, i, j);
                if (j != k)
                    swap(nums, i, k);
                j++;
                k++;
            }
        }
    }
}