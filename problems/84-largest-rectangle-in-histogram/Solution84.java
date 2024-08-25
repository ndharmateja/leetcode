import java.util.Stack;

@SuppressWarnings("unused")
class Solution84 {
    static class Bar {
        int height;
        int count;

        public Bar(int height, int count) {
            this.height = height;
            this.count = count;
        }
    }

    // O(n^2) time and O(1) space solution
    // Using a stack
    private int solution2(int[] heights) {
        int maxArea = 0;

        Stack<Bar> stack = new Stack<>();
        for (int height : heights) {
            while (!stack.isEmpty() && stack.peek().height > height) {
                Bar popped = stack.pop();
                int area = popped.height * popped.count;
                if (area > maxArea) {
                    maxArea = area;
                }
            }
            for (Bar bar : stack) {
                bar.count++;
            }
            if (stack.isEmpty() || stack.peek().height != height) {
                stack.push(new Bar(height, 0));
            } 
        }

        while (!stack.isEmpty()) {
            Bar popped = stack.pop();
            int area = popped.height * popped.count;
            if (area > maxArea) {
                maxArea = area;
            }
        }

        return maxArea;
    }

    // O(n^3) time and O(1) space solution
    // Brute force
    private int solution1(int[] heights) {
        return -1;
    }

    public int largestRectangleArea(int[] heights) {
        return solution2(heights);
    }
}