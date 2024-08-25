import java.util.Stack;

class Solution155 {

    private Stack<Integer> stack;
    private Stack<Integer> minValues;

    public Solution155() {
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

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(val);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */