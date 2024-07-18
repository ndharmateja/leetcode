import java.util.Stack;

class Solution20 {
    private static boolean isOpening(char c) {
        return c == '(' || c == '{' || c == '[';
    }

    private static boolean isClosing(char c) {
        return c == ')' || c == '}' || c == ']';
    }

    private static boolean areMatching(char opening, char closing) {
        return (opening == '(' && closing == ')')
                || (opening == '{' && closing == '}')
                || (opening == '[' && closing == ']');
    }

    public boolean isValid(String s) {
        Stack<Character> stack = new Stack<>();

        for (char c : s.toCharArray()) {
            if (isOpening(c)) {
                stack.push(c);
            } else if (isClosing(c)) {
                // If the character doesn't match with the top stack char
                // or if the stack is empty, it is not valid
                if (stack.isEmpty() || !areMatching(stack.pop(), c))
                    return false;
            }

            // We don't need to do anything if char is anything other than
            // a closing or an opening bracket
        }

        // If the stack is non-empty after going through all the chars
        // it is not valid
        return stack.isEmpty();
    }
}