import java.util.LinkedList;
import java.util.Queue;

@SuppressWarnings("unused")
class Solution1448 {
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
        int maxSoFar;

        public Pair(TreeNode node, int maxSoFar) {
            this.node = node;
            this.maxSoFar = maxSoFar;
        }
    }

    // O(n) time and O(n) space solution
    // Do level order traversal while storing the max so far from
    // the root to the node, so that we can find the good nodes
    private int solution1(TreeNode root) {
        if (root == null)
            return 0;

        // Root will be always counted as 1
        int count = 1;

        // Create queue and add root
        Queue<Pair> q = new LinkedList<>();
        q.add(new Pair(root, root.val));

        // We will increment the count while adding the children
        // to the queue
        while (!q.isEmpty()) {
            Pair curr = q.poll();

            // Add left child to queue
            // and if it is a good node, increment count
            TreeNode left = curr.node.left;
            if (left != null) {
                if (left.val >= curr.maxSoFar)
                    count++;
                q.add(new Pair(left, Math.max(curr.maxSoFar, left.val)));
            }

            // same with right node
            TreeNode right = curr.node.right;
            if (right != null) {
                if (right.val >= curr.maxSoFar)
                    count++;
                q.add(new Pair(right, Math.max(curr.maxSoFar, right.val)));
            }
        }

        return count;
    }

    // O(n) time and O(height) space solution
    // Reference: https://youtu.be/7cp5imvDzl4
    // Recursive solution using DFS (preorder traversal)
    private int solution2(TreeNode node, int maxValue) {
        if (node == null)
            return 0;

        // If curr node is good node, we initialize the count to 1
        // else to 0
        // and update maxValue
        int numGoodNodes = node.val >= maxValue ? 1 : 0;
        maxValue = Math.max(maxValue, node.val);

        // Recursively get the number of good nodes from
        // both the children
        numGoodNodes += solution2(node.left, maxValue);
        numGoodNodes += solution2(node.right, maxValue);

        return numGoodNodes;
    }

    public int goodNodes(TreeNode root) {
        return solution2(root, Integer.MIN_VALUE);
    }
}