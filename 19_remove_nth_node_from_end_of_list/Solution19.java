@SuppressWarnings("unused")
class Solution19 {
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

    // Use two pointers
    // Advance first pointer 'n+1' times ahead (If it reaches null midway
    // it means that we have to delete the head)
    // Second pointer will still be at head
    // Now move both pointers one by one till first pointer reaches null
    // Remove the node after the second pointer
    private ListNode solution1(ListNode head, int n) {
        ListNode advance = head;
        ListNode curr = head;

        for (int i = 0; i < n + 1; i++) {
            if (advance == null) {
                return head.next;
            }
            advance = advance.next;
        }

        while (advance != null) {
            advance = advance.next;
            curr = curr.next;
        }

        curr.next = curr.next.next;

        return head;
    }

    private ListNode solution2(ListNode head, int n) {
        ListNode curr = head;
        int size = 0;

        while (curr != null) {
            curr = curr.next;
            size++;
        }

        if (size == n) {
            return head.next;
        }

        curr = head;
        for (int i = 0; i < (size - n) - 1; i++) {
            curr = curr.next;
        }

        curr.next = curr.next.next;

        return head;
    }

    public ListNode removeNthFromEnd(ListNode head, int n) {
        return solution2(head, n);
    }
}