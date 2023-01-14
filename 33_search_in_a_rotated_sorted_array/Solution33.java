@SuppressWarnings("unused")
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

    private void reverse(int[] nums, int low, int high) {
        while (low < high) {
            swap(nums, low++, high--);
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    private void rotateArray(int[] nums, int k) {
        k = k % nums.length;
        reverse(nums, 0, nums.length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.length - 1);
    }

    private int binarySearch(int[] nums, int target, int low, int high) {
        if (low > high)
            return -1;
        int mid = (low + high) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] < target)
            return binarySearch(nums, target, mid + 1, high);
        return binarySearch(nums, target, low, mid - 1);
    }

    private int findPivotIndex(int[] nums) {
        int low = 0;
        int high = nums.length - 1;
        if (nums[low] < nums[high])
            return 0;
        if (nums.length == 2 && nums[0] > nums[1])
            return 1;

        while (low < high) {
            if (high - low == 1)
                return high;

            int mid = (low + high) / 2;
            if (nums[mid] < nums[mid - 1]) {
                return mid;
            } else if (nums[mid] < nums[high]) {
                high = mid;
            } else if (nums[mid] > nums[high]) {
                low = mid;
            }
        }
        return low;
    }

    // O(n) time and O(1) space solution
    // Method:
    // 1. Find pivot where it is rotated
    // 2. Rotate the array to make it ascending
    // 3. Do binary search on the sorted array
    private int solution2(int[] nums, int target) {
        int pivot = findPivotIndex(nums);
        if (pivot != 0) {
            rotateArray(nums, nums.length - pivot);
        }

        int index = binarySearch(nums, target, 0, nums.length - 1);
        return index == -1 ? -1 : (index + pivot) % nums.length;
    }

    public int search(int[] nums, int target) {
        return solution2(nums, target);
    }
}