import java.util.ArrayList;
import java.util.List;

class Solution145 {
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

    private void postorderTraversal(TreeNode root, List<Integer> order) {
        if (root == null)
            return;
        postorderTraversal(root.left, order);
        postorderTraversal(root.right, order);
        order.add(root.val);
    }

    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> order = new ArrayList<>();
        postorderTraversal(root, order);
        return order;
    }
}