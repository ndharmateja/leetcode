class BSTIterator {
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

    TreeNode nextNode;

    public BSTIterator(TreeNode root) {
        this.nextNode = root;
        while (this.nextNode.left != null) {
            this.nextNode = this.nextNode.left;
        }
    }

    public int next() {
        int toReturn = this.nextNode.val;
        this.nextNode = inorderSuccessor(this.nextNode);
        return toReturn;
    }

    private TreeNode inorderSuccessor(TreeNode node) {
        return null;
    }

    public boolean hasNext() {
        return this.nextNode != null;
    }
}
