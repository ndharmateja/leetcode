import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

class Solution347 {

    // O(n log n) solution
    @SuppressWarnings("unused")
    private int[] solution1(int[] nums, int k) {
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

    // Reference: https://www.youtube.com/watch?v=YPTqKIgVk-k
    // O(n) solution
    private int[] solution2(int[] nums, int k) {
        // 1. Get counts of all elements
        Map<Integer, Integer> counts = new HashMap<>();
        for (int num : nums)
            counts.put(num, counts.getOrDefault(num, 0) + 1);

        // 2. Create an array such that at a particular index 'i'
        // we store the list of elements with count 'i'
        // the max size of this array is 'n + 1' where n - num of elements in nums
        // Because count can be atmost 'n' (if all elements are same)
        @SuppressWarnings("unchecked")
        List<Integer>[] array = new List[nums.length + 1];
        for (int key : counts.keySet()) {
            int count = counts.get(key);
            if (array[count] == null) {
                array[count] = new ArrayList<>();
            }
            array[count].add(key);
        }

        // 3. Scan the above array from right to left and add 'k' elements
        int[] output = new int[k];
        int i = 0;
        for (int j = array.length - 1; j >= 0; j--) {
            List<Integer> elements = array[j];
            if (elements == null)
                continue;
            for (int element : elements) {
                // Stop if 'k' elements are added already
                if (i == k)
                    break;
                output[i++] = element;
            }
        }
        return output;
    }

    public int[] topKFrequent(int[] nums, int k) {
        return solution2(nums, k);
    }
}