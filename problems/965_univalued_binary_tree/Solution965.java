class Solution965 {
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

    public boolean isUnivalTree(TreeNode root) {
        if (root == null)
            return true;
        boolean isRootValueSameAsChildren = true;
        if (root.left != null && root.val != root.left.val) {
            isRootValueSameAsChildren = false;
        }
        if (root.right != null && root.val != root.right.val) {
            isRootValueSameAsChildren = false;
        }
        return isUnivalTree(root.left) && isUnivalTree(root.right) && isRootValueSameAsChildren;
    }
}