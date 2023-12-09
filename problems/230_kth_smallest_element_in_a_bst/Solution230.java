import java.util.HashMap;
import java.util.Stack;

@SuppressWarnings("unused")
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
        return solution2(root, k);
    }

    /**
     * Iterative inorder
     * Stop when we visit k nodes
     * 
     * Reference: https://youtu.be/5LUXSvjmGCw?t=165
     * 
     * @param root
     * @param k    - 1-indexed
     * @return
     */
    private int solution2(TreeNode root, int k) {
        TreeNode curr = root;
        Stack<TreeNode> stack = new Stack<>();
        int numVisited = 0;

        while (curr != null || !stack.isEmpty()) {
            // If curr node is null
            // We pop node from stack (thereby increasing numVisited)
            // and then process its right child
            if (curr == null) {
                curr = stack.pop();
                numVisited++;

                // If numVisited becomes k
                // the kth element is the popped element
                if (numVisited == k)
                    return curr.val;

                curr = curr.right;
            }

            // If curr node is not null
            // we add it to the stack
            // and process its left child
            else {
                stack.push(curr);
                curr = curr.left;
            }
        }

        // We will reach here in case k <= 0 or k > size of tree
        return -1;
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
     * @param x
     * @param rank - 0-indexed
     * @return
     */
    private int select(TreeNode x, int rank, HashMap<TreeNode, Integer> nodeCounts) {
        // Get size of left subtree
        int leftSize = size(x.left, nodeCounts);

        // If the left tree size is more than rank
        // then the answer is the rank'th element in the left subtree
        if (leftSize > rank)
            return select(x.left, rank, nodeCounts);

        // If the left tree size is less than rank
        // then the answer is (rank - (1 + leftSize))th element in the right subtree
        if (leftSize < rank)
            return select(x.right, rank - (1 + leftSize), nodeCounts);

        // If the left tree size is equal to rank
        // then the answer is 'x' itself
        return x.val;
    }

    /**
     * Returns the count of number of nodes
     * in the tree rooted at x
     * Uses memoization in HashMap
     * If not already present, calculates recursively and stores
     * in the map
     * 
     * @param x
     * @param nodeCounts
     * @return
     */
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