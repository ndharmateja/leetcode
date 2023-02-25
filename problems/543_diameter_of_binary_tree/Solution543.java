class Solution543 {
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

    private int[] getHeightDiameter(TreeNode node) {
        // Base case
        if (node == null)
            return new int[] { -1, -1 };

        // get height and diameter of left child
        int[] leftHD = getHeightDiameter(node.left);
        int leftH = leftHD[0];
        int leftD = leftHD[1];

        // get height and diameter of right child
        int[] rightHD = getHeightDiameter(node.right);
        int rightH = rightHD[0];
        int rightD = rightHD[1];

        // height of curr node
        int height = 1 + Math.max(leftH, rightH);

        // diameter of curr node -> max of left child dia, right child dia and diameter
        // of a path passing through curr node
        int diameter = Math.max(1 + leftH + rightH, Math.max(leftD, rightD));

        // Return height and diameter
        return new int[] { height, diameter };
    }

    public int diameterOfBinaryTree(TreeNode root) {
        return this.getHeightDiameter(root)[1];
    }
}