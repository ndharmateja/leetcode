class Solution105 {
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

    private TreeNode buildTree(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
        // base case
        if (preEnd < preStart)
            return null;

        // Create root
        int rootValue = preorder[preStart];
        TreeNode root = new TreeNode(rootValue);

        // Find index of root in inorder
        int inorderRootIndex = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == rootValue) {
                inorderRootIndex = i;
            }
        }
        int numElementsInLeftSubtree = inorderRootIndex - inStart;

        // Assign left and right children
        // using recursive calls
        root.left = buildTree(preorder, preStart + 1, preStart + numElementsInLeftSubtree, inorder, inStart,
                inorderRootIndex - 1);
        root.right = buildTree(preorder, preStart + numElementsInLeftSubtree + 1, preEnd, inorder, inorderRootIndex + 1,
                inEnd);

        // return root
        return root;
    }

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return buildTree(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }
}