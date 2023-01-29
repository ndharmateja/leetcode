@SuppressWarnings("unused")
class Solution167 {

    // Returns the index of the "key" in the array "numbers"
    // such that the index is not "indexFlag"
    // Uses binary search
    // Returns -1 if key doesn't exist or the only index where key
    // exists is "indexFlag"
    private int arrayContains(int[] numbers, int key, int indexFlag) {
        int low = 0;
        int high = numbers.length - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (numbers[mid] == key) {
                // If "mid" is not equal to "indexFlag"
                // we return "mid"
                if (mid != indexFlag)
                    return mid;

                // When "mid" is equal to "indexFlag"
                // check values at mid - 1 and mid + 1
                else if (mid - 1 >= low && numbers[mid - 1] == key)
                    return mid - 1;
                else if (mid + 1 <= high && numbers[mid + 1] == key)
                    return mid + 1;

                // and if they don't match, we return -1
                else
                    return -1;
            } else if (key < numbers[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return -1;
    }

    // O(n log n) solution
    // For each element, use binary search to find "target" - "element"
    private int[] solution1(int[] numbers, int target) {
        // For each "number" in array, try to find index of
        // "target" - "number"
        for (int i = 0; i < numbers.length; i++) {
            int number = numbers[i];

            // Get the index of "target - number" such that
            // the returned index is not "i"
            int complementNumberIndex = arrayContains(numbers, target - number, i);

            // If such index exists, return the values
            if (complementNumberIndex != -1) {
                return new int[] { i + 1, complementNumberIndex + 1 };
            }
        }

        // We wouldn't reach here as we are guaranteed a solution
        return null;
    }

    // O(n) solution
    // using two pointers, from left and right
    // Reference: https://youtu.be/cQ1Oz4ckceM?t=236
    //
    // Method:
    // 1. Initialize 2 pointers: left=0 right=numbers.length - 1
    // 2. If sum of numbers at indices left and right:
    // - a. > target, we decrement 'right' by 1 (because we want to decrease our
    // target
    // sum and array is sorted)
    // - b. < target, we increment 'left' by 1 (because we want to increase our
    // target
    // sum and array is sorted)
    // - c. = target, we return the indices
    public int[] solution2(int[] numbers, int target) {
        int left = 0;
        int right = numbers.length - 1;

        while (left < right) {
            if (numbers[left] + numbers[right] > target) {
                right--;
                continue;
            }
            if (numbers[left] + numbers[right] < target) {
                left++;
                continue;
            }
            return new int[] { left + 1, right + 1 };
        }

        // We wouldn't reach here as we are guaranteed a solution
        return null;
    }

    public int[] twoSum(int[] numbers, int target) {
        return solution2(numbers, target);
    }
}