class Solution33 {
    // O(n) time and O(1) space solution
    // Linear Search
    private int solution1(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
    public int search(int[] nums, int target) {
        return -1;
    }
}