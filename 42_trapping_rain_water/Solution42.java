import java.util.ArrayList;
import java.util.List;

class Solution42 {
    public int trap(int[] height) {
        return solution1(height);
    }

    // O(n) time
    // Method:
    // 1. Find all local maximas - O(n)
    // 2. Find all trap indices (between which water is trapped) - O(n)
    // 3. Calculate the total volume of water - O(n)
    public int solution1(int[] height) {
        if (height.length < 3)
            return 0;

        List<Integer> maximumIndices = getMaximumIndices(height);
        if (maximumIndices.isEmpty() || maximumIndices.size() == 1) {
            return 0;
        }

        List<Integer> trapIndices = getTrapIndices(height, maximumIndices);

        return getTotalWater(height, trapIndices);
    }

    // After finding one local max, we have to find the local min
    // first before finding the next local max
    // Also handles the edge cases of local maxima
    private List<Integer> getMaximumIndices(int[] height) {
        int n = height.length;
        List<Integer> maximumIndices = new ArrayList<>();
        boolean findingMax = true;
        if (height[0] > height[1]) {
            findingMax = false;
            maximumIndices.add(0);
        }

        for (int i = 1; i < n - 1; i++) {
            if (findingMax && height[i] >= height[i - 1] && height[i] > height[i + 1]) {
                findingMax = false;
                maximumIndices.add(i);
            } else if (!findingMax && height[i] <= height[i - 1] && height[i] < height[i + 1]) {
                findingMax = true;
            }
        }

        if (findingMax && height[n - 2] <= height[n - 1]) {
            maximumIndices.add(n - 1);
        }

        return maximumIndices;
    }

    // The list of trap start and end points are a subset of the
    // maximum indices
    // Start one pointer from left, and keep finding the next local max
    // that is greater than equal to the current trap index, and that
    // will be the end of the current trap of water
    // Do the same from the right until we have covered all the traps
    // and meet in the middle
    private List<Integer> getTrapIndices(int[] height, List<Integer> maximumIndices) {
        List<Integer> trapIndices = new ArrayList<>();

        int l = maximumIndices.get(0);
        trapIndices.add(l);
        int numTrapsFromLeft = 1;
        for (int i = 1; i < maximumIndices.size(); i++) {
            if (height[maximumIndices.get(i)] >= height[l]) {
                numTrapsFromLeft++;
                l = maximumIndices.get(i);
                trapIndices.add(l);
            }
        }

        int r = maximumIndices.get(maximumIndices.size() - 1);
        if (l != r) {
            trapIndices.add(r);
            for (int i = maximumIndices.size() - 2; i > 0; i--) {
                if (maximumIndices.get(i) == l) {
                    break;
                }
                if (height[maximumIndices.get(i)] >= height[r]) {
                    r = maximumIndices.get(i);
                    trapIndices.add(numTrapsFromLeft, r);
                }
            }
        }

        return trapIndices;
    }

    // Given the list of trap points
    // This function iterates through all of them and
    // calculates the total volume of water
    private int getTotalWater(int[] height, List<Integer> trapIndices) {
        int totalWater = 0;
        for (int i = 0; i < trapIndices.size() - 1; i++) {
            int trapStartIndex = trapIndices.get(i);
            int trapEndIndex = trapIndices.get(i + 1);
            int waterElevation = Math.min(height[trapStartIndex], height[trapEndIndex]);

            for (int j = trapStartIndex; j <= trapEndIndex; j++) {
                totalWater += Math.max(waterElevation - height[j], 0);
            }
        }

        return totalWater;
    }

}