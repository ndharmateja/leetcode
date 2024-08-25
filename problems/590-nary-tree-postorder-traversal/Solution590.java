import java.util.ArrayList;
import java.util.List;

class Solution590 {
    static class Node {
        public int val;
        public List<Node> children;

        public Node() {
        }

        public Node(int _val) {
            val = _val;
        }

        public Node(int _val, List<Node> _children) {
            val = _val;
            children = _children;
        }
    };

    private void postorder(Node root, List<Integer> order) {
        if (root == null)
            return;
        for (Node child : root.children) {
            postorder(child, order);
        }
        order.add(root.val);
    }

    public List<Integer> postorder(Node root) {
        List<Integer> order = new ArrayList<>();
        postorder(root, order);
        return order;
    }
}