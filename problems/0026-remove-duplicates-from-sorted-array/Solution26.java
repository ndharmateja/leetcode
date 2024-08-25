import java.util.Arrays;

class Solution26 {
    public int removeDuplicates(int[] nums) {
        int i = 0;

        for (int j = 1; j < nums.length; j++) {
            if (nums[j] > nums[i]) {
                i++;
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
            System.out.println(Arrays.toString(nums));
        }
        return i + 1;
    }

    public static void main(String[] args) {
        int[] nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        System.out.println(new Solution26().removeDuplicates(nums));
    }
}