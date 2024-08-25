class Solution110 {
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
        int height;
        boolean isBalanced;

        public Pair(int height, boolean isBalanced) {
            this.height = height;
            this.isBalanced = isBalanced;
        }
    }

    // Recursive function that calculates the height of the curr node
    // and if the node is balanced
    private Pair balance(TreeNode node) {
        if (node == null) {
            return new Pair(0, true);
        }

        Pair leftNB = balance(node.left);
        Pair rightNB = balance(node.right);

        int height = 1 + Math.max(leftNB.height, rightNB.height);
        boolean isBalanced = leftNB.isBalanced && rightNB.isBalanced
                && (Math.abs(leftNB.height - rightNB.height) <= 1);

        return new Pair(height, isBalanced);
    }

    public boolean isBalanced(TreeNode root) {
        return balance(root).isBalanced;
    }
}