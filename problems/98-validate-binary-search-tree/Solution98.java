class Solution98 {
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    public boolean isValidBST(TreeNode root, long lowerLimit, long upperLimit) {
        if (root == null)
            return true;
        return isValidBST(root.left, lowerLimit, root.val)
                && isValidBST(root.right, root.val, upperLimit)
                && root.val > lowerLimit
                && root.val < upperLimit;
    }

    public boolean isValidBST(TreeNode root) {
        return isValidBST(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
}