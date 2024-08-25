import java.util.HashMap;
import java.util.Map;

class Solution974 {
    private int getPositiveRemainder(int n, int k) {
        return ((n % k) + k) % k;
    }

    public int subarraysDivByK(int[] nums, int k) {
        // Keys will be
        Map<Integer, Integer> prefixRemainderCounts = new HashMap<>();
        prefixRemainderCounts.put(0, 1);

        int output = 0;
        int currPrefixSum = 0;
        for (int num : nums) {
            System.out.println(prefixRemainderCounts);
            currPrefixSum += num;

            int remainder = getPositiveRemainder(currPrefixSum, k);
            output += prefixRemainderCounts.getOrDefault(k - remainder, 0);

            prefixRemainderCounts.put(remainder, prefixRemainderCounts.getOrDefault(remainder, 0) + 1);
        }

        return output;
    }

    public static void main(String[] args) {
        System.out.println(new Solution974().subarraysDivByK(new int[] { 4, 5, 0, -2, -3, 1 }, 5));
    }
}