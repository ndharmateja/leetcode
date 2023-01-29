import java.util.Stack;

class Solution1019 {
    static class ListNode {
        int val;
        ListNode next;

        ListNode() {
        }

        ListNode(int val) {
            this.val = val;
        }

        ListNode(int val, ListNode next) {
            this.val = val;
            this.next = next;
        }
    }

    static class Pair {
        int value;
        int index;

        public Pair(int value, int index) {
            this.value = value;
            this.index = index;
        }
    }

    private int getListSize(ListNode head) {
        ListNode curr = head;
        int size = 0;
        while (curr != null) {
            size++;
            curr = curr.next;
        }
        return size;
    }

    // O(n) time and O(n) space solution
    // See the 739_daily_temperatures for reference
    public int[] nextLargerNodes(ListNode head) {
        int size = getListSize(head);
        int[] output = new int[size];

        // Monotonically non-increasing stack
        Stack<Pair> stack = new Stack<>();
        int i = 0;
        ListNode curr = head;

        while (curr != null) {
            // Remove all the values from the stack
            // that are less than the curr val
            while (!stack.isEmpty() && stack.peek().value < curr.val) {
                Pair pair = stack.pop();
                output[pair.index] = curr.val;
            }

            // Add curr node to the stack
            stack.push(new Pair(curr.val, i++));
            curr = curr.next;
        }

        // For all the remaining values in the stack
        // there is no greater value
        while (!stack.isEmpty()) {
            output[stack.pop().index] = 0;
        }

        return output;
    }
}