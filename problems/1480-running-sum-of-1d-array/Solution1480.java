class Solution1480 {
    public int[] runningSum(int[] nums) {
        int[] array = new int[nums.length];
        array[0] = nums[0];
        for (int i = 1; i < array.length; i++) {
            array[i] = array[i - 1] + nums[i];
        }
        return array;
    }
}