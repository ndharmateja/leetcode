import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class Solution56 {
    public int[][] merge(int[][] intervals) {
        ArrayList<int[]> mergedList = new ArrayList<>();
        Arrays.sort(intervals, new Comparator<int[]>() {
            public int compare(int[] o1, int[] o2) {
                return o1[0] - o2[0];
            }
        });

        int[] currInterval = intervals[0];
        for (int i = 0; i < intervals.length; i++) {
            int[] interval = intervals[i];
            if (interval[0] <= currInterval[1])
                currInterval[1] = Integer.max(currInterval[1], interval[1]);
            else {
                mergedList.add(currInterval);
                currInterval = interval;
            }
            if (i == intervals.length - 1)
                mergedList.add(currInterval);
        }

        return mergedList.toArray(new int[0][0]);
    }

    public static void main(String[] args) {
        System.out.println(Arrays.deepToString(
                new Solution56().merge(new int[][] {
                        { 1, 3 },
                        { 15, 18 },
                        { 2, 6 },
                        { 8, 10 },
                })));
    }
}
