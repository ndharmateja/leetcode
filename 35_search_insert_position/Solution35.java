class Solution35 {
    public int searchInsert(int[] nums, int target, int low, int high) {
        if (low == high) {
            if (nums[low] >= target)
                return low;
            return low + 1;
        }
        if (high - low == 1) {
            if (nums[low] >= target)
                return low;
            if (nums[high] >= target)
                return high;
            return high + 1;
        }
        int mid = (low + high) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] > target)
            return searchInsert(nums, target, low, mid - 1);
        return searchInsert(nums, target, mid + 1, high);
    }

    public int searchInsert(int[] nums, int target) {
        return searchInsert(nums, target, 0, nums.length - 1);
    }

    public static void main(String[] args) {
        System.out.println(new Solution35().searchInsert(new int[] { 1, 3, 5, 6 }, 7));
    }
}