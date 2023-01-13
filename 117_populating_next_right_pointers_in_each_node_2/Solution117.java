import java.util.LinkedList;
import java.util.Queue;

class Solution117 {
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

    static class Pair {
        Node node;
        int level;

        public Pair(Node node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    // O(n) time and O(n) space solution
    public Node connect(Node root) {
        if (root == null)
            return null;

        Queue<Pair> queue = new LinkedList<>();

        Pair prev = null;
        queue.add(new Pair(root, 0));

        // Level order traversal but with two pointers
        // to track curr and prev
        // We also store the level in the queue
        // If prev and curr's levels are same, then
        // prev.next is curr
        // Otherwise prev.next is null
        while (!queue.isEmpty()) {
            Pair curr = queue.remove();

            // prev null check for the first node
            if (prev != null) {
                if (prev.level != curr.level) {
                    prev.node.next = null;
                } else {
                    prev.node.next = curr.node;
                }
            }
            prev = curr;

            if (curr.node.left != null)
                queue.add(new Pair(curr.node.left, curr.level + 1));
            if (curr.node.right != null)
                queue.add(new Pair(curr.node.right, curr.level + 1));
        }

        return root;
    }
}