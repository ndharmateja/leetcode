import java.util.ArrayList;
import java.util.PriorityQueue;

public class Solution56 {
    public int[][] merge(int[][] intervals) {
        // Edge case - only one interval
        // we return intervals itself
        if (intervals.length <= 1)
            return intervals;

        // Priority queue so that we get intervals in increasing order
        // of starts of intervals
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        for (int[] interval : intervals)
            pq.add(interval);

        ArrayList<int[]> mergedList = new ArrayList<>();
        int[] currMerged = pq.poll();
        while (!pq.isEmpty()) {
            int[] currInterval = pq.poll();
            // If currInterval has an intersection with currMerged
            // merge them and store in currInterval
            if (currInterval[0] <= currMerged[1])
                currMerged[1] = Integer.max(currMerged[1], currInterval[1]);

            // If no intersection
            // add the currMerged to the mergedIntervals list
            // and make the currInterval the currMerged
            else {
                mergedList.add(currMerged);
                currMerged = currInterval;
            }

            // If this is the last interval we are processing
            // we add the currMerged to the mergedList
            if (pq.isEmpty())
                mergedList.add(currMerged);
        }

        return mergedList.toArray(new int[0][0]);
    }
}
