import java.util.Arrays;

class Solution128 {
    // O(n log n) solution
    private int solution1(int[] nums) {
        // 1. Sort the array
        Arrays.sort(nums);
        int maxLongest = -1;
        int currLongest = 0;

        // 2. Iterate over the array
        for (int i = 0; i < nums.length; i++) {
            if (i == 0) {
                currLongest = 1;
                continue;
            }
            // Skip duplicates
            if (nums[i] == nums[i - 1]) {
                continue;
            }

            // Increment currLongest if element at 'i' is greater
            // than the element at 'i - 1' by 1
            if (nums[i] - nums[i - 1] == 1) {
                currLongest++;
                continue;
            }

            // Sequence broken
            // so reset 'currLongest' to 1
            // and also update maxLongest if applicable
            if (currLongest > maxLongest) {
                maxLongest = currLongest;
            }
            currLongest = 1;
        }

        // Update maxLongest after loop as well
        // in cases where the longest sequence is at the end
        // of the array
        if (currLongest > maxLongest) {
            maxLongest = currLongest;
        }

        return maxLongest;
    }

    public int longestConsecutive(int[] nums) {
        return solution1(nums);
    }

}