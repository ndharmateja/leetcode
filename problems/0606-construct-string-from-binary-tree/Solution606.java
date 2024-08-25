class Solution606 {
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

    public String tree2str(TreeNode root) {
        if (root == null)
            return "";

        StringBuilder builder = new StringBuilder();
        builder.append(root.val);

        if (root.left == null && root.right == null) {
            return builder.toString();
        }

        builder.append(String.format("(%s)", tree2str(root.left)));
        if (root.right != null)
            builder.append(String.format("(%s)", tree2str(root.right)));

        return builder.toString();
    }
}