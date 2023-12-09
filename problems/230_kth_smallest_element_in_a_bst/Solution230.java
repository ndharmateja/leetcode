import java.util.HashMap;

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

    /**
     * 
     * @param root
     * @param k    - 1-indexed
     * @return
     */
    public int kthSmallest(TreeNode root, int k) {
        return solution1(root, k);
    }

    /**
     * 
     * @param root
     * @param k    - 1-indexed
     * @return
     */
    private int solution1(TreeNode root, int k) {
        HashMap<TreeNode, Integer> nodeCounts = new HashMap<>();
        return select(root, k - 1, nodeCounts);
    }

    /**
     * 
     * @param root
     * @param rank - 0-indexed
     * @return
     */
    private int select(TreeNode root, int rank, HashMap<TreeNode, Integer> nodeCounts) {
        int leftSize = size(root.left, nodeCounts);
        if (leftSize > rank)
            return select(root.left, rank, nodeCounts);
        if (leftSize < rank)
            return select(root.right, rank - (1 + leftSize), nodeCounts);
        return root.val;
    }

    private int size(TreeNode x, HashMap<TreeNode, Integer> nodeCounts) {
        if (x == null)
            return 0;
        if (!nodeCounts.containsKey(x)) {
            int size = 1 + size(x.left, nodeCounts) + size(x.right, nodeCounts);
            nodeCounts.put(x, size);
        }
        return nodeCounts.get(x);
    }
}