import java.util.Stack;

class Solution20 {
    private boolean isOpening(char c) {
        return c == '(' || c == '[' || c == '{';
    }

    private boolean isMatching(char opening, char closing) {
        return (opening == '(' && closing == ')') || (opening == '[' && closing == ']')
                || (opening == '{' && closing == '}');
    }

    public boolean isValid(String s) {
        Stack<Character> stack = new Stack<>();
        for (char c : s.toCharArray()) {
            if (isOpening(c)) {
                stack.add(c);
            } else {
                if (stack.isEmpty()) {
                    return false;
                }
                char opening = stack.pop();
                if (!isMatching(opening, c)) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }
}