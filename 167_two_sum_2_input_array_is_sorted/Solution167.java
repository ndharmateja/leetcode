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
    public int[] solution1(int[] numbers, int target) {
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
        return null;
    }

    public int[] twoSum(int[] numbers, int target) {
        return solution1(numbers, target);
    }
}