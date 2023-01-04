import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution1636 {
    public int[] frequencySort(int[] nums) {
        // 1. Get counts of all elements
        Map<Integer, Integer> counts = new HashMap<>();
        for (int num : nums)
            counts.put(num, counts.getOrDefault(num, 0) + 1);

        // 2. Create an array such that at a particular index 'i'
        // we store the list of elements with count 'i'
        // the max size of this array is 'n + 1' where n - num of elements in nums
        // Because count can be atmost 'n' (if all elements are same)
        @SuppressWarnings("unchecked")
        List<Integer>[] reverseCounts = new List[nums.length + 1];
        for (int key : counts.keySet()) {
            int count = counts.get(key);
            if (reverseCounts[count] == null) {
                reverseCounts[count] = new ArrayList<>();
            }
            reverseCounts[count].add(key);
        }
        System.out.println(Arrays.toString(reverseCounts));

        // 3. Scan the above array from right to left and add 'k' elements
        int[] output = new int[nums.length];
        int count = 0;
        for (int j = 0; j < reverseCounts.length; j++) {
            List<Integer> elements = reverseCounts[j];
            if (elements == null)
                continue;
            Collections.sort(elements, new Comparator<Integer>() {
                @Override
                public int compare(Integer o1, Integer o2) {
                    return -(o1 - o2);
                }
            });
            for (Integer element : elements) {
                for (int k = 0; k < j; k++) {
                    output[count] = element;
                    count++;
                }
            }
        }
        return output;
    }
}