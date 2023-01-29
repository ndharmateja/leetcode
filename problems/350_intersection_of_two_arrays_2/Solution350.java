import java.util.HashMap;

class Solution350 {
    public int[] intersect(int[] nums1, int[] nums2) {
        HashMap<Integer, Integer> counts1 = new HashMap<>();
        for (Integer n : nums1) {
            counts1.put(n, counts1.getOrDefault(n, 0) + 1);
        }

        HashMap<Integer, Integer> counts2 = new HashMap<>();
        for (Integer n : nums2) {
            counts2.put(n, counts2.getOrDefault(n, 0) + 1);
        }

        // Store the intersection counts in counts1
        // with value for keys not present in counts2 as -1
        int outputArraySize = 0;
        for (int n : counts1.keySet()) {
            if (!counts2.containsKey(n)) {
                counts1.replace(n, -1);
            } else {
                int nCount = Math.min(counts1.get(n), counts2.get(n));
                outputArraySize += nCount;
                counts1.put(n, nCount);
            }
        }

        int[] output = new int[outputArraySize];
        int i = 0;
        for (int n : counts1.keySet()) {
            int nCount = counts1.get(n);
            if (nCount == -1)
                continue;
            for (int j = 0; j < nCount; j++) {
                output[i++] = n;
            }
        }
        return output;
    }
}