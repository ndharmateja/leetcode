import java.util.Arrays;

class Solution27 {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int removeElement(int[] nums, int val) {
        int count = 0;
        for (int i = nums.length - 1; i >= 0; i--) {
            if (nums[i] == val)
                count++;
            else
                break;
        }

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == val) {
                swap(nums, i, nums.length - count - 1);
                count++;
            }
            if (i > nums.length - count) {
                break;
            }
        }
        return nums.length - count;
    }

    public static void main(String[] args) {
        int[] nums = new int[] { 3, 2, 2, 3 };
        int k = new Solution27().removeElement(nums, 3);
        System.out.println(k);
        System.out.println(Arrays.toString(nums));
    }
}