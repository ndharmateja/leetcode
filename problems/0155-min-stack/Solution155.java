import java.util.Stack;

@SuppressWarnings("unused")
class Solution155 {
    private class MinStack1 {
        private Stack<Long> packedStack;

        // long x = 0xFFFFFFFFL; // x = 2^32-1
        // long y = 0xFFFFFFFF; // y = -1
        private static final long F_32 = 0xFFFFFFFFL;

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
            return unpackVal(this.packedStack.peek());
        }

        public int getMin() {
            return unpackMin(this.packedStack.peek());
        }

        private static long pack(int min, int val) {
            return ((long) min << 32) | (val & F_32);
        }

        private static int unpackMin(long top) {
            return (int) (top >> 32);
        }

        private static int unpackVal(long top) {
            return (int) (top & F_32);
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