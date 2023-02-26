import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

@SuppressWarnings("unused")
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

    // O(n) time and O(n) space solution (n - num nodes in tree)
    // Do a level order traversal (right to left on each level)
    // and add the node's value to the list for every new level
    private List<Integer> solution1(TreeNode root) {
        final class Pair {
            TreeNode node;
            int level;

            public Pair(TreeNode node, int level) {
                this.node = node;
                this.level = level;
            }
        }

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

    // O(n) time and O(n) space solution (n - num nodes in tree)
    // Similar to solution1
    // Except no extra class for storing level
    // We handle each level in one iteration
    // In first iteration, we have all the nodes from level 0 (root)
    // in the queue
    // In the second iteration we have all the nodes from level 1
    // in the queue
    // In each iteration we can remove all the nodes from the queue
    // and add their children to the queue
    // And if we do level order traversal from right to left,
    // in each iteration we can add the value of the first element in the level
    // to the output list
    private List<Integer> solution2(TreeNode root) {
        // Create list for the output
        List<Integer> output = new ArrayList<>();

        // return empty list if root is null
        if (root == null)
            return output;

        // Queue for level order traversal from right to left
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);

        // Loop to handle each level
        while (!q.isEmpty()) {

            // Add the value of head of queue to the output list
            // First value in the curr level is the last node int the level
            // as we are adding the nodes from right to left
            output.add(q.peek().val);

            // Remove each node in the level
            // and its non-null children to the queue;
            // We need number of nodes in the curr level
            // as a variable because we also keep adding their children
            // and we can't run this loop until the queue is empty
            int numNodesInLevel = q.size();
            for (int i = 0; i < numNodesInLevel; i++) {
                TreeNode curr = q.poll();

                // We add right first as we are doing level order
                // from right to left
                if (curr.right != null)
                    q.add(curr.right);
                if (curr.left != null)
                    q.add(curr.left);
            }

        }

        return output;
    }

    public List<Integer> rightSideView(TreeNode root) {
        return solution1(root);
    }
}