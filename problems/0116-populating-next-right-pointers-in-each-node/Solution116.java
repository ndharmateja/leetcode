import java.util.LinkedList;
import java.util.Queue;

class Solution116 {
    static class Node {
        public int val;
        public Node left;
        public Node right;
        public Node next;

        public Node() {
        }

        public Node(int _val) {
            val = _val;
        }

        public Node(int _val, Node _left, Node _right, Node _next) {
            val = _val;
            left = _left;
            right = _right;
            next = _next;
        }
    }

    private static boolean isPowerOfTwoMinusOne(int n) {
        // n + 1 should be a power of 2
        // log_2(n + 1) should be an integer
        return (Math.log(n) / Math.log(2)) % 1 == 0;
    }

    // O(n) time and O(n) space solution
    public Node connect(Node root) {
        if (root == null)
            return null;

        Queue<Node> queue = new LinkedList<>();

        Node prev = null;
        int count = 0;
        queue.add(root);

        // Level order traversal but with two pointers
        // to track curr and prev
        // Since it is a perfect binary tree
        // the next node will be null for every node
        // which is in form of 2^k - 1
        // For other nodes, prev.next will be curr
        while (!queue.isEmpty()) {
            Node curr = queue.remove();
            count++;

            // prev null check for the first node
            if (prev != null) {
                if (isPowerOfTwoMinusOne(count)) {
                    prev.next = null;
                } else {
                    prev.next = curr;
                }
            }
            prev = curr;

            if (curr.left != null)
                queue.add(curr.left);
            if (curr.right != null)
                queue.add(curr.right);
        }

        return root;
    }
}