import java.util.ArrayList;
import java.util.List;

class Solution94 {
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

    private void inorderTraversal(TreeNode root, List<Integer> order) {
        if (root == null)
            return;
        inorderTraversal(root.left, order);
        order.add(root.val);
        inorderTraversal(root.right, order);
    }

    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> order = new ArrayList<>();
        inorderTraversal(root, order);
        return order;
    }
}