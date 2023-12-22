import java.util.ArrayList;
import java.util.List;

public class Solution57 {
    private boolean hasIntersection(int[] interval1, int[] interval2) {
        // Intervals are not intersecting if start of interval is greater than
        // the end of another
        int start1 = interval1[0];
        int end1 = interval1[1];
        int start2 = interval2[0];
        int end2 = interval2[1];

        boolean areNotIntersecting = start1 > end2 || start2 > end1;
        return !areNotIntersecting;
    }

    private boolean greater(int[] interval1, int[] interval2) {
        return interval1[0] > interval2[1];
    }

    private int[] merge(int[] interval1, int[] interval2) {
        return new int[] { Math.min(interval1[0], interval2[0]), Math.max(interval1[1], interval2[1]) };
    }

    public int[][] insert(int[][] intervals, int[] toInsert) {
        // Start the mergedInterval with the new interval to be inserted
        int[] mergedInterval = toInsert;
        List<int[]> output = new ArrayList<>();

        for (int[] interval : intervals) {
            // If current interval is intersecting with the merged interval
            // merge the curr interval as well
            if (mergedInterval != null && hasIntersection(interval, mergedInterval)) {
                mergedInterval = merge(interval, mergedInterval);
                continue;
            }

            // mergedInterval is null if it is already added to output
            // If mergedInterval has not already been added to the output
            // and the curr interval is greater than the merged interval
            // it means that we need to add the mergedInterval to output
            // and make it null
            if (mergedInterval != null && greater(interval, mergedInterval)) {
                output.add(mergedInterval);
                mergedInterval = null;
            }

            // Either case we add the current interval to output (because no intersection
            // with the merged interval)
            output.add(interval);
        }

        // The merged interval could be greater than all the intervals
        // and that case is handled here
        if (mergedInterval != null) {
            output.add(mergedInterval);
        }

        return output.toArray(new int[output.size()][]);
    }

    public static void main(String[] args) {
        System.out.println(new Solution57().insert(new int[][] { { 1, 5 } }, new int[] { 2, 3 }));
    }
}