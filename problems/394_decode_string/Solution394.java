import java.util.Stack;

class Solution394 {
    private String formString(Stack<Character> stack, StringBuilder builder) {
        builder.setLength(0);
        while (!stack.isEmpty()) {
            builder.append(stack.pop());
        }
        return builder.reverse().toString();
    }

    // O(n) time and O(n) space solution
    // Reference: https://www.youtube.com/watch?v=qB0zZpBJlh8
    public String decodeString(String s) {
        Stack<Character> stack = new Stack<>();
        StringBuilder builder = new StringBuilder();

        for (char c : s.toCharArray()) {
            // If char is ']'
            // get all the chars till we get '['
            // those chars need to be repeated 'k' times
            // After getting '['
            // Form 'k' with all the next digits in the stack
            // Add these chars to the stack back 'k' times
            if (c == ']') {
                // Store chars in builder
                while (stack.peek() != '[') {
                    builder.append(stack.pop());
                }

                // Pop '['
                stack.pop();

                // Get 'k'
                StringBuilder numBuilder = new StringBuilder();
                while (!stack.isEmpty() && Character.isDigit(stack.peek())) {
                    numBuilder.append(stack.pop());
                }
                int k = Integer.parseInt(numBuilder.reverse().toString());

                // Add chars 'k' times
                for (int i = 0; i < k; i++) {
                    // Iterate over builder in reverse
                    // and add each char to stack
                    for (int j = builder.length() - 1; j >= 0; j--) {
                        stack.push(builder.charAt(j));
                    }
                }

                // Reset builder
                builder.setLength(0);
            }
            // If any other char, we just add it to stack
            else {
                stack.push(c);
            }
        }

        // Return the string formed by stack
        return formString(stack, builder);
    }

    public static void main(String[] args) {
        Solution394 s = new Solution394();
        System.out.println(s.decodeString("100[abc]"));
    }
}