import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Solution199 {
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    static class Pair {
        TreeNode node;
        int level;

        public Pair(TreeNode node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    // O(n) time and O(n) space solution (n - num nodes in tree)
    // Do a level order traversal (right to left on each level)
    // and add the node's value to the list for every new level
    public List<Integer> rightSideView(TreeNode root) {
        // Create list for the output
        List<Integer> output = new ArrayList<>();

        // return empty list if root is null
        if (root == null)
            return output;

        // Store the previous node to add to list
        // whenever there is a level change
        Pair prev = new Pair(null, -1);

        // Queue for level order traversal from right to left
        Queue<Pair> q = new LinkedList<>();
        q.add(new Pair(root, 0));
        while (!q.isEmpty()) {
            Pair curr = q.poll();

            // Add curr node value to list if there is a level change
            if (curr.level != prev.level) {
                output.add(curr.node.val);
            }

            // Add children to the queue if they are not null
            // we add right first and then left (because we need right to left level order)
            if (curr.node.right != null)
                q.add(new Pair(curr.node.right, curr.level + 1));
            if (curr.node.left != null)
                q.add(new Pair(curr.node.left, curr.level + 1));

            // Update prev to curr value
            prev = curr;
        }

        return output;
    }
}