import java.util.Stack;

class Solution739 {
    static class Pair {
        int temperature;
        int index;

        public Pair(int temperature, int index) {
            this.temperature = temperature;
            this.index = index;
        }
    }

    // O(n) time and O(n) space solution
    // Reference: https://youtu.be/cTBiBSnjO3c
    // Method:
    // 1. We store a non-decreasing stack
    // 2. Every time we get a new temperature, we pop all the temperatures
    // that are smaller than the current temperature and update the
    // output for all the removed temperatures
    // 3. We add that temperature to the stack
    // 4. At the end, for all the remaining elements in the stack,
    // there are no elements on the right that are greater than it.
    public int[] dailyTemperatures(int[] temperatures) {
        int[] output = new int[temperatures.length];
        Stack<Pair> stack = new Stack<>();

        for (int i = 0; i < temperatures.length; i++) {
            int temperature = temperatures[i];
            while (!stack.isEmpty() && temperature > stack.peek().temperature) {
                Pair popped = stack.pop();
                output[popped.index] = i - popped.index;
            }
            stack.push(new Pair(temperature, i));
        }

        while (!stack.isEmpty()) {
            output[stack.pop().index] = 0;
        }

        return output;
    }
}