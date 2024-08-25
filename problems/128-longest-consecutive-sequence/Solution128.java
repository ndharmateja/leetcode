import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

@SuppressWarnings("unused")
class Solution128 {
    // O(n log n) solution
    private int solution1(int[] nums) {
        // 1. Sort the array
        Arrays.sort(nums);
        int maxSequenceLength = -1;
        int currSequenceLength = 0;

        // 2. Iterate over the array
        for (int i = 0; i < nums.length; i++) {
            if (i == 0) {
                currSequenceLength = 1;
                continue;
            }
            // Skip duplicates
            if (nums[i] == nums[i - 1]) {
                continue;
            }

            // Increment currLongest if element at 'i' is greater
            // than the element at 'i - 1' by 1
            if (nums[i] - nums[i - 1] == 1) {
                currSequenceLength++;
                continue;
            }

            // Sequence broken
            // so reset 'currLongest' to 1
            // and also update maxLongest if applicable
            if (currSequenceLength > maxSequenceLength) {
                maxSequenceLength = currSequenceLength;
            }
            currSequenceLength = 1;
        }

        // Update maxLongest after loop as well
        // in cases where the longest sequence is at the end
        // of the array
        if (currSequenceLength > maxSequenceLength) {
            maxSequenceLength = currSequenceLength;
        }

        return maxSequenceLength;
    }

    // O(n) solution
    // Reference: https://youtu.be/P6RZZMu_maU
    //
    // Method:
    // 1. Add all nums from array to set (to optimize array contains operations)
    // 2. Iterate over all the numbers
    // - a. We skip numbers that are not the start of the sequence (a number
    // - is start of the sequence if number - 1 is not present in the set)
    // - b. For each start of the sequence we find the length of that sequence
    // - and update max sequence length if it is greater
    private int solution2(int[] nums) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums)
            numSet.add(num);

        int maxSequenceLength = 0;
        for (int num : nums) {
            // Skip numbers that are not the start
            // of a sequence
            if (numSet.contains(num - 1)) {
                continue;
            }

            // Find the length of that particular sequence
            int currSequenceLength = 1;
            int currNum = num + 1;
            while (numSet.contains(currNum)) {
                currNum++;
                currSequenceLength++;
            }

            // Update the length of the longest sequence appropriately
            if (currSequenceLength > maxSequenceLength) {
                maxSequenceLength = currSequenceLength;
            }
        }

        return maxSequenceLength;
    }

    public int longestConsecutive(int[] nums) {
        return solution2(nums);
    }

}