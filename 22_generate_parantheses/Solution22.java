import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Solution22 {
    // Reference: https://youtu.be/s9fokUqJ76A
    // Ideas:
    // 1. number of total open and close parantheses should be each equal to 'n'
    // 2. At any stage, numOpen must be greater than or equal to
    // numClose. Eg ()) => numOpen = 1, numClose = 2 is not valid
    // => We can add an opening paranthesis if numOpen < n
    // and we add a closing paranthesis if numClose < numOpen
    // and it is valid if numOpen = numClose = n
    public List<String> generateParenthesis(int n) {
        return solution1(n);
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