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

    public int maxArea(int[] height) {
        return solution1(height);
    }

}