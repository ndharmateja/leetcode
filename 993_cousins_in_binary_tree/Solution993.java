class Solution993 {
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

    private int getDepth(TreeNode root, int x, int depth) {
        if (root.val == x) {
            return depth;
        }
        if (x < root.val) {
            return getDepth(root.left, x, depth + 1);
        }
        return getDepth(root.right, x, depth + 1);
    }

    public boolean isCousins(TreeNode root, int x, int y) {
        return getDepth(root, x, 0) == getDepth(root, y, 0);
    }
}