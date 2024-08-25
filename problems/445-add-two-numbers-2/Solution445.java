class Solution445 {
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

    public ListNode reverseList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    // O(n) time and O(n) space solution
    // Improvement: Store the result in the larger of l1 and l2 (O(1) space)
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        // Reverse linked lists to add the digits in order
        l1 = reverseList(l1);
        l2 = reverseList(l2);

        int carry = 0;
        ListNode dummy = new ListNode();
        ListNode curr = dummy;
        while (l1 != null || l2 != null) {
            // Get two curr digits
            int digit1 = l1 != null ? l1.val : 0;
            int digit2 = l2 != null ? l2.val : 0;

            // Get the sum and carry
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;

            // Create a new node with the sum digit
            curr.next = new ListNode(sum % 10);
            curr = curr.next;

            // Go to the next nodes
            if (l1 != null)
                l1 = l1.next;
            if (l2 != null)
                l2 = l2.next;
        }

        // Add carry at the end if applicable
        if (carry != 0) {
            curr.next = new ListNode(carry);
        }

        // Return the reversed list
        return reverseList(dummy.next);
    }
}