class Solution230 {
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

    static class MutableInteger {
        int value;

        public MutableInteger(int value) {
            this.value = value;
        }

        void increment() {
            this.value++;
        }

        int getValue() {
            return this.value;
        }
    }

    private int solution1(TreeNode root, int k) {
        return -1;
    }

    public int kthSmallest(TreeNode root, int k) {
        return solution1(root, k);
    }
}