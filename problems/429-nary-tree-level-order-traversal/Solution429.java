import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Solution429 {
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
    }

    static class Pair {
        Node node;
        int level;

        Pair(Node node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    public List<List<Integer>> levelOrder(Node root) {
        List<List<Integer>> output = new ArrayList<>();

        if (root == null) {
            return output;
        }

        Queue<Pair> queue = new LinkedList<>();
        queue.add(new Pair(root, 0));

        int currLevel = -1;
        while (!queue.isEmpty()) {
            Pair curr = queue.poll();
            if (curr.node == null)
                continue;

            if (curr.level != currLevel) {
                currLevel = curr.level;
                output.add(new ArrayList<>());
            }
            output.get(currLevel).add(curr.node.val);

            // Add children to queue
            for (Node child : curr.node.children) {
                queue.add(new Pair(child, curr.level + 1));
            }
        }

        return output;
    }

}
