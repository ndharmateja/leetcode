import java.util.Stack;

class Solution150 {
    private boolean isNumber(String token) {
        try {
            Integer.parseInt(token);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    // O(n) time and O(n) space
    public int evalRPN(String[] tokens) {
        Stack<Integer> stack = new Stack<>();
        for (String token : tokens) {
            if (isNumber(token)) {
                stack.push(Integer.parseInt(token));
                continue;
            }

            int val2 = stack.pop();
            int val1 = stack.pop();
            if (token.equals("+"))
                stack.push(val1 + val2);
            else if (token.equals("-"))
                stack.push(val1 - val2);
            else if (token.equals("*"))
                stack.push(val1 * val2);
            else if (token.equals("/"))
                stack.push(val1 / val2);
        }
        return stack.pop();
    }
}