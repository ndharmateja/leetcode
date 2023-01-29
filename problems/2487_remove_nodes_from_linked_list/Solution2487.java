import java.util.Stack;

class Solution2487 {
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

    // O(n) time and O(1) space solution
    // Refer 739
    public ListNode removeNodes(ListNode head) {
        // Sentinel node
        ListNode dummy = new ListNode(Integer.MAX_VALUE, head);
        dummy.next = head;

        // Create stack with dummy element
        // At any point, the stack will have all the
        // nodes connected to each other
        Stack<ListNode> stack = new Stack<>();
        stack.push(dummy);

        ListNode curr = head;
        while (curr != null) {
            // Remove all nodes from stack that have
            // a lesser value than the current node
            // Stack will never get empty as dummy node will always be
            // there as its values is Integer.MAX_VALUE
            while (stack.peek().val < curr.val) {
                stack.pop();
            }

            // The top most node in the stack should point to
            // the current node
            stack.peek().next = curr;

            // Add curr node to the stack and go to next node
            stack.push(curr);
            curr = curr.next;
        }

        return dummy.next;
    }
}