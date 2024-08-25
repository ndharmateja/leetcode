class Solution129 {
    public class TreeNode {
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

    // O(n) time and O(h) space (recursion stack)
    // recursive solution, that takes the number formed so far
    private int solution1(TreeNode node, int numSoFar) {
        // If node is null, we return 0
        if (node == null) {
            return 0;
        }

        // Compute the new numSoFar
        numSoFar = numSoFar * 10 + node.val;

        // If leaf, the return value is the new numSoFar itself
        if (node.left == null && node.right == null) {
            return numSoFar;
        }

        // Otherwise, we recursively call the function on both the children
        return solution1(node.left, numSoFar) + solution1(node.right, numSoFar);
    }

    public int sumNumbers(TreeNode root) {
        return solution1(root, 0);
    }
}