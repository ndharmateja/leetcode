public class Solution124 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
    }

    private static class MaxSum {
        int endingAtRoot;
        int notEndingAtRoot;

        public MaxSum(int sumEndingAtRoot, int sumNotEndingAtRoot) {
            this.endingAtRoot = sumEndingAtRoot;
            this.notEndingAtRoot = sumNotEndingAtRoot;
        }

        public int max() {
            return Integer.max(endingAtRoot, notEndingAtRoot);
        }
    }

    private static final int NEG_INF = Integer.MIN_VALUE;

    public int maxPathSum(TreeNode root) {
        MaxSum sums = maxPathSumHelper(root);
        return sums.max();
    }

    /**
     * returns negative infinity if any of the values is negative infinity
     * otherwise returns the sum
     * 
     * @param a
     * @param b
     * @return
     */
    private int sum(int a, int b) {
        return sum(a, b, 0);
    }

    /**
     * returns negative infinity if any of the values is negative infinity
     * otherwise returns the sum
     * 
     * @param a
     * @param b
     * @param c
     * @return
     */
    private int sum(int a, int b, int c) {
        if (a == NEG_INF || b == NEG_INF || c == NEG_INF)
            return NEG_INF;
        return a + b + c;
    }

    private int max(int a, int b) {
        return Integer.max(a, b);
    }

    private int max(int a, int b, int c) {
        return max(a, max(b, c));
    }

    private int max(int a, int b, int c, int d, int e) {
        return max(max(a, b, c), max(d, e));
    }

    private MaxSum maxPathSumHelper(TreeNode x) {
        if (x == null)
            return new MaxSum(NEG_INF, NEG_INF);

        MaxSum leftMaxSum = maxPathSumHelper(x.left);
        MaxSum rightMaxSum = maxPathSumHelper(x.right);

        // sum ending at root
        //
        // Can either be this value itself
        // or this val + sum ending at root for the left tree
        // or this val + sum ending at root for the right tree
        //
        // so we take the max of these 3
        int sumEndingAtRoot = max(
                x.val,
                sum(x.val, leftMaxSum.endingAtRoot),
                sum(x.val, rightMaxSum.endingAtRoot));

        // sum not ending at root
        //
        // can either be sum not ending at root of the left tree
        // or the sum not ending at root of the left tree
        // or sum ending at root of the left tree
        // or sum ending at root of the right tree
        // or this value + (sums ending at root for both children)
        //
        // so we take the max among these 5 values
        int sumNotEndingAtRoot = max(
                leftMaxSum.notEndingAtRoot,
                rightMaxSum.notEndingAtRoot,
                leftMaxSum.endingAtRoot,
                rightMaxSum.endingAtRoot,
                sum(x.val, leftMaxSum.endingAtRoot, rightMaxSum.endingAtRoot));

        return new MaxSum(sumEndingAtRoot, sumNotEndingAtRoot);
    }
}
