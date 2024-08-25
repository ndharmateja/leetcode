import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

@SuppressWarnings("unused")
class Solution22 {

    public List<String> generateParenthesis(int n) {
        return solution2(n);
    }

    // Creates string from a stack of characters
    private String createString(Stack<Character> stack) {
        StringBuilder builder = new StringBuilder();
        for (char c : stack) {
            builder.append(c);
        }
        return builder.toString();
    }

    // Recursive backtracking algorithm
    private void backtrack(Stack<Character> stack, List<String> output, int numOpen, int numClosed, int n) {
        if (numClosed == n && numOpen == n) {
            output.add(this.createString(stack));
            return;
        }
        if (numOpen < n) {
            stack.push('(');
            backtrack(stack, output, numOpen + 1, numClosed, n);
            stack.pop();
        }
        if (numClosed < numOpen) {
            stack.push(')');
            backtrack(stack, output, numOpen, numClosed + 1, n);
            stack.pop();
        }
    }

    // Reference: https://youtu.be/s9fokUqJ76A
    // Ideas:
    // 1. number of total open and close parantheses should be each equal to 'n'
    // 2. At any stage, numOpen must be greater than or equal to
    // numClose. Eg ()) => numOpen = 1, numClose = 2 is not valid
    // => We can add an opening paranthesis if numOpen < n
    // and we add a closing paranthesis if numClose < numOpen
    // and it is valid if numOpen = numClose = n
    private List<String> solution2(int n) {
        Stack<Character> stack = new Stack<>();
        List<String> output = new ArrayList<>();

        // Run the backtracking algorithm
        backtrack(stack, output, 0, 0, n);

        return output;
    }

    // We also store numOpen and numClose
    // because it saves us from computing it for every string
    static class Node {
        String value;
        int numOpen;
        int numClose;

        public Node(String value, int numOpen, int numClose) {
            this.value = value;
            this.numOpen = numOpen;
            this.numClose = numClose;
        }
    }

    // Using a level order traversal of the tree in method.jpeg
    private List<String> solution1(int n) {
        List<String> output = new ArrayList<>();

        // Queue with the empty string
        Queue<Node> queue = new LinkedList<>();
        queue.add(new Node("", 0, 0));

        // while queue is not empty
        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            // if valid node, add it to output
            if (curr.numClose == n && curr.numClose == n) {
                output.add(curr.value);
            }

            // Add open bracket if numOpen < n
            if (curr.numOpen < n) {
                queue.add(new Node(curr.value + "(", curr.numOpen + 1, curr.numClose));
            }

            // Add close bracket if numClose < numOpen
            if (curr.numClose < curr.numOpen) {
                queue.add(new Node(curr.value + ")", curr.numOpen, curr.numClose + 1));
            }
        }

        return output;
    }
}