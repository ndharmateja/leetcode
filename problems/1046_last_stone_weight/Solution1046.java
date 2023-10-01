import java.util.PriorityQueue;

public class Solution1046 {
    // O(n log n) time and O(n) space
    public int lastStoneWeight(int[] stones) {
        // Create a min heap
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        // Add all negative values stones to the heap (because we need a max heap)
        for (Integer stone : stones) {
            minHeap.add(-stone);
        }

        // As long as the heap contains more than one element
        // do the process
        while (minHeap.size() > 1) {
            int max1 = -minHeap.poll();
            int max2 = -minHeap.poll();
            // max1 >= max2
            if (max1 != max2)
                minHeap.add(-(max1 - max2));
        }

        // If heap is empty return 0, otherwise return the element
        return minHeap.isEmpty() ? 0 : -minHeap.poll();
    }
}
