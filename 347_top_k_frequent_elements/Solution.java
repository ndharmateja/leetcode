import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

class Solution {
    public int[] topKFrequent(int[] nums, int k) {

        // 1. Get counts of all elements
        Map<Integer, Integer> counts = new HashMap<>();
        for (int num : nums)
            counts.put(num, counts.getOrDefault(num, 0) + 1);

        // 2. Sort the elements based on counts
        // improvement: Build heap from the counts and get top k - runs in O(k log n)
        List<Entry<Integer, Integer>> entries = new ArrayList<>(counts.entrySet());
        Collections.sort(entries, new Comparator<Entry<Integer, Integer>>() {
            @Override
            public int compare(Entry<Integer, Integer> e1, Entry<Integer, Integer> e2) {
                return -(e1.getValue() - e2.getValue());
            }
        });

        // 3. Return top k
        int[] output = new int[k];
        for (int i = 0; i < k; i++) {
            output[i] = entries.get(i).getKey();
        }
        return output;
    }
}