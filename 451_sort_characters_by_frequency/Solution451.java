import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution451 {
    public String frequencySort(String s) {
        // 1. Get counts of all elements
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : s.toCharArray())
            counts.put(c, counts.getOrDefault(c, 0) + 1);

        // 2. Create an array such that at a particular index 'i'
        // we store the list of elements with count 'i'
        // the max size of this array is 'n + 1' where n - num of elements in nums
        // Because count can be atmost 'n' (if all elements are same)
        @SuppressWarnings("unchecked")
        List<Character>[] reverseCounts = new List[s.length() + 1];
        for (Character c : counts.keySet()) {
            int count = counts.get(c);
            if (reverseCounts[count] == null) {
                reverseCounts[count] = new ArrayList<>();
            }
            reverseCounts[count].add(c);
        }

        // 3. Scan the above array from right to left and add 'k' elements
        StringBuilder builder = new StringBuilder();
        for (int j = reverseCounts.length - 1; j >= 0; j--) {
            List<Character> chars = reverseCounts[j];
            if (chars == null)
                continue;
            for (Character c : chars) {
                for (int k = 0; k < j; k++) {
                    builder.append(c);
                }
            }
        }
        return builder.toString();
    }
}