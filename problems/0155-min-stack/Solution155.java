import java.util.Stack;

@SuppressWarnings("unused")
class Solution155 {
    private class MinStack1 {
        private Stack<Long> packedStack;

        public MinStack1() {
            this.packedStack = new Stack<>();
        }

        public void push(int val) {
            int min = this.packedStack.isEmpty() || val < this.getMin() ? val : this.getMin();
            this.packedStack.add(pack(min, val));
        }

        public void pop() {
            this.packedStack.pop();
        }

        public int top() {
            return (int) (this.packedStack.peek() & 0xFFFFFFFFL);
        }

        public int getMin() {
            return (int) (this.packedStack.peek() >> 32);
        }

        private long pack(int min, int val) {
            return ((long) min << 32) | (val & 0xFFFFFFFFL);
        }
    }

    private class MinStack2 {
        private Stack<Integer> stack;
        private Stack<Integer> minValues;

        public MinStack2() {
            stack = new Stack<>();
            minValues = new Stack<>();
        }

        public void push(int val) {
            if (stack.isEmpty()) {
                stack.push(val);
                minValues.push(val);
                return;
            }
            stack.push(val);
            if (minValues.peek() > val) {
                minValues.push(val);
            } else {
                minValues.push(minValues.peek());
            }
        }

        public void pop() {
            stack.pop();
            minValues.pop();
        }

        public int top() {
            return stack.peek();
        }

        public int getMin() {
            return minValues.peek();
        }
    }
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(val);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */