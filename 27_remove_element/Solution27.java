import java.util.Arrays;

class Solution27 {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int removeElement(int[] nums, int val) {
        int j = nums.length - 1;
        for (int i = nums.length - 1; i >= 0; i--) {
            if (nums[i] == val) {
                swap(nums, i, j);
                j--;
            }
        }
        return j + 1;
    }

    public static void main(String[] args) {
        int[] nums = new int[] { 3, 2, 2, 3 };
        int k = new Solution27().removeElement(nums, 3);
        System.out.println(k);
        System.out.println(Arrays.toString(nums));
    }
}