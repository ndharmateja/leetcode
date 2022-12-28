public class Solution704 {

    private int search(int[] nums, int target, int low, int high) {
        if (low > high)
            return -1;
        int mid = (low + high) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] < target)
            return search(nums, target, mid + 1, high);
        return search(nums, target, low, mid - 1);
    }

    public int search(int[] nums, int target) {
        return search(nums, target, 0, nums.length - 1);
    }
}