import java.util.Arrays;

@SuppressWarnings("unused")
class Solution189 {
    public void rotate(int[] nums, int k) {
        // solution2(nums, k);
        solution1(nums, k, 0, nums.length - 1);
    }

    private void reverse(int[] nums, int low, int high) {
        while (low < high) {
            swap(nums, low++, high--);
        }
    }

    // O(n) time and O(1) space solution, 7
    // Eg: [1, 2, 3, 4, 5, 6, 7] and k = 3
    // Reverse whole array => [7, 6, 5, 4, 3, 2, 1]
    // Reverse first 'k' elements => [5, 6, 7, 4, 3, 2, 1]
    // Reverse last 'n - k' elements => [5, 6, 7, 1, 2, 3, 4]
    private void solution4(int[] nums, int k) {
        k = k % nums.length;
        reverse(nums, 0, nums.length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.length - 1);
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // O(n) time and O(1) space solution
    // Recursive solution
    // For the exact methodology, see method.jpeg pic
    private void solution1(int[] nums, int k, int low, int high) {
        int numElements = high - low + 1;
        k = k % numElements;
        if (k == 0)
            return;
        if (2 * k > numElements) {
            // kPrime is n - k
            int kPrime = numElements - k;
            for (int i = low; i < low + kPrime; i++) {
                swap(nums, i, i + kPrime);
            }
            solution1(nums, k - kPrime, low + kPrime, high);
        } else {
            int kPrime = numElements - k;
            for (int i = low; i < low + k; i++) {
                swap(nums, i, i + kPrime);
            }
            solution1(nums, k, low + k, high);
        }
    }

    // O(n) time and O(1) space
    // Create a new array copy
    // Copy the last 'k' elements
    // and then the first 'k' at the end of the array
    private void solution2(int[] nums, int k) {
        k = k % nums.length;
        int[] copy = new int[nums.length];
        for (int i = 0; i < k; i++) {
            copy[i] = nums[nums.length - k + i];
        }
        for (int i = k; i < copy.length; i++) {
            copy[i] = nums[i - k];
        }
        for (int i = 0; i < copy.length; i++) {
            nums[i] = copy[i];
        }
    }

    // O(kn) time solution
    // Do a single rotation 'k' times
    private void solution3(int[] nums, int k) {
        k = k % nums.length;
        for (int i = 0; i < k; i++) {
            int lastNum = nums[nums.length - 1];
            // Shift all elements from index '0'
            // one position right
            for (int j = nums.length - 1; j > 0; j--) {
                nums[j] = nums[j - 1];
            }

            // Make the old last number as the new first number
            nums[0] = lastNum;
        }
    }

    public static void main(String[] args) {
        int[] nums = { 1, 2, 3, 4, 5, 6, 7 };
        Solution189 s = new Solution189();
        s.rotate(nums, 3);
        System.out.println(Arrays.toString(nums));
    }
}