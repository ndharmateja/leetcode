import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Solution103 {
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

    static class Pair {
        TreeNode node;
        int level;

        Pair(TreeNode node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> output = new ArrayList<>();

        if (root == null) {
            return output;
        }

        Queue<Pair> queue = new LinkedList<>();
        queue.add(new Pair(root, 0));

        boolean leftToRight = false;
        int currLevel = -1;
        while (!queue.isEmpty()) {
            Pair curr = queue.poll();
            if (curr.node == null)
                continue;

            if (curr.level != currLevel) {
                currLevel = curr.level;
                output.add(new ArrayList<>());
                leftToRight = !leftToRight;
            }
            if (leftToRight) {
                output.get(currLevel).add(curr.node.val);
            } else {
                output.get(currLevel).add(0, curr.node.val);
            }

            // Add children to queue
            queue.add(new Pair(curr.node.left, curr.level + 1));
            queue.add(new Pair(curr.node.right, curr.level + 1));
        }

        return output;
    }
}