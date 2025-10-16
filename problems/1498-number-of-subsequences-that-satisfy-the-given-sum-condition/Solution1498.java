import java.util.Arrays;

@SuppressWarnings("unused")
public class Solution1498 {
    private static int min(int a, int b) {
        return a < b ? a : b;
    }

    private static int max(int a, int b) {
        return a > b ? a : b;
    }

    // O(2^n) time and O(n) space
    // O(n) space is for the stack
    // Brute force solution - checks for all the subsequences
    // At the deepest recursive call, the number of frames in the stack
    // will be n - the number of elements in the nums array
    private int solution1(int[] nums, int i, int minValue, int maxValue, int targetSum, int sequenceLength) {
        // When we reach the end of the array
        // that is when the sequence is completed
        // So if the sequence is not empty and if minValue + maxValue <= targetSum
        // we return 1 as we want to count this sequence
        if (i == nums.length) {
            if (sequenceLength > 0 && minValue + maxValue <= targetSum)
                return 1;
            return 0;
        }

        // For each index 'i' we either choose the element
        // at that index or not choose that element
        // That is how we get all the subsequences

        // 1. Choose the element at 'i'
        // and if we are choosing it, we need to update the minValue and maxValue
        // accordingly and the sequenceLength also increases by 1
        // and recursively call the function on the next index
        int result = 0;
        result += solution1(nums, i + 1, min(minValue, nums[i]), max(maxValue, nums[i]), targetSum, sequenceLength + 1);

        // 2. Do not choose the element at 'i' and run it on the next
        // index recursively
        result += solution1(nums, i + 1, minValue, maxValue, targetSum, sequenceLength);

        // Return the count of subsequences with a matching target sum
        return result % 1000_000_007;
    }

    private int solution1(int[] nums, int targetSum) {
        return solution1(nums, 0, Integer.MAX_VALUE, Integer.MIN_VALUE, targetSum, 0);
    }

    // O(n^2) time
    private int solution2(int[] nums, int targetSum) {
        // Compute powers of 2
        int n = nums.length;
        int MOD = 1_000_000_007;
        int[] pow2 = new int[n];
        pow2[0] = 1;
        for (int i = 1; i < n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        // Sort the array
        Arrays.sort(nums);
        int totalSubsequences = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > targetSum / 2)
                break;
            for (int j = i; j < n; j++) {
                if (nums[i] + nums[j] > targetSum)
                    break;

                // Count all the non empty subsequences that start with nums[i]
                // and end with nums[j]
                // It is equal to the number of subsequences (empty or not) formed by
                // the j - i - 1 elements between these two ends
                if (i == j)
                    totalSubsequences += 1;
                else
                    totalSubsequences += pow2[j - i - 1];
                totalSubsequences %= MOD;
            }
        }
        return totalSubsequences;
    }

    // TODO: Both solution 1 and 2 are exceeding time limit
    public int numSubseq(int[] nums, int targetSum) {
        return solution2(nums, targetSum);
    }

    public static void main(String[] args) {
        System.out.println(new Solution1498().numSubseq(new int[] { 3, 5, 6, 7 }, 9));

        System.out
                .println(new Solution1498().numSubseq(
                        new int[] { 14, 4, 6, 6, 20, 8, 5, 6, 8, 12, 6, 10, 14, 9, 17, 16, 9, 7, 14, 11, 14, 15, 13,
                                11, 10, 18, 13, 17, 17, 14, 17, 7, 9, 5, 10, 13, 8, 5, 18, 20, 7, 5, 5, 15, 19, 14 },
                        22));
    }
}
