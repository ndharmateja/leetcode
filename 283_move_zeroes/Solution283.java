import java.util.Arrays;

class Solution283 {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public void moveZeroes(int[] nums) {
        int j = nums.length - 1;
        for (int i = nums.length - 1; i >= 0; i--) {
            if (nums[i] == 0) {
                swap(nums, i, j);
                j--;
            }
        }
    }

    public static void main(String[] args) {
        int[] nums = new int[] { 0, 1, 0, 3, 12 };
        new Solution283().moveZeroes(nums);
        System.out.println(Arrays.toString(nums));
    }
}