class Solution101 {
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

    // O(n) time & O(height) space solution
    private boolean isSymmetric(TreeNode node1, TreeNode node2) {
        if (node1 == null && node2 == null)
            return true;
        if (node1 == null || node2 == null)
            return false;
        return node1.val == node2.val && isSymmetric(node1.left, node2.right) && isSymmetric(node1.right, node2.left);
    }

    public boolean isSymmetric(TreeNode root) {
        if (root == null)
            return true;
        return isSymmetric(root.left, root.right);
    }
}