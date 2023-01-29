import java.util.HashMap;
import java.util.Map;

class Solution2341 {
    public int[] numberOfPairs(int[] nums) {
        Map<Integer, Integer> counts = new HashMap<>();
        for (int num : nums) {
            counts.put(num, counts.getOrDefault(num, 0) + 1);
        }

        int numPairs = 0;
        int numLeftOver = 0;
        for (int count : counts.values()) {
            numPairs += count / 2;
            numLeftOver += count % 2;
        }

        return new int[] { numPairs, numLeftOver };
    }
}