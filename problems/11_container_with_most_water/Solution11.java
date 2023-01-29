@SuppressWarnings("unused")
class Solution11 {

    // Brute force solution - check all containers
    private int solution1(int[] height) {
        int maxArea = 0;
        for (int l = 0; l < height.length - 1; l++) {
            for (int r = l + 1; r < height.length; r++) {
                int area = Math.min(height[l], height[r]) * (r - l);
                maxArea = Math.max(maxArea, area);
            }
        }
        return maxArea;
    }

    // O(n) solution
    // Reference: https://youtu.be/UuiTKBwPgAo
    // Initialize left and right pointers at start and end of array
    // If current area greater than max area, update
    // if height of left is less than height of right, increase left pointer
    // else decrease right pointer
    private int solution2(int[] height) {
        int l = 0;
        int r = height.length - 1;
        int maxArea = 0;

        while (l < r) {
            int area = Math.min(height[l], height[r]) * (r - l);
            maxArea = Math.max(maxArea, area);
            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        return maxArea;
    }

    public int maxArea(int[] height) {
        return solution2(height);
    }

}