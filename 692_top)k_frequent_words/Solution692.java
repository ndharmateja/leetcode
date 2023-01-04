import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution692 {
    // Reference: https://www.youtube.com/watch?v=YPTqKIgVk-k
    // O(n) solution
    private List<String> solution2(String[] words, int k) {
        // 1. Get counts of all elements
        Map<String, Integer> counts = new HashMap<>();
        for (String word : words)
            counts.put(word, counts.getOrDefault(word, 0) + 1);

        // 2. Create an array such that at a particular index 'i'
        // we store the list of elements with count 'i'
        // the max size of this array is 'n + 1' where n - num of elements in nums
        // Because count can be atmost 'n' (if all elements are same)
        @SuppressWarnings("unchecked")
        List<String>[] reverseCounts = new List[words.length + 1];
        for (String key : counts.keySet()) {
            int count = counts.get(key);
            if (reverseCounts[count] == null) {
                reverseCounts[count] = new ArrayList<>();
            }
            reverseCounts[count].add(key);
        }

        // 3. Scan the above array from right to left and add 'k' elements
        List<String> output = new ArrayList<>();
        int count = 0;
        for (int j = reverseCounts.length - 1; j >= 0; j--) {
            List<String> elements = reverseCounts[j];
            if (elements == null)
                continue;
            Collections.sort(elements);
            for (String element : elements) {
                output.add(element);
                count++;
                // Stop if 'k' elements are added already
                if (count == k)
                    return output;
            }
        }
        return output;
    }

    public List<String> topKFrequent(String[] words, int k) {
        return solution2(words, k);
    }

    public static void main(String[] args) {
        System.out.println(
                new Solution692().topKFrequent(new String[] { "i", "love", "leetcode", "i", "love", "coding" }, 2));
    }
}