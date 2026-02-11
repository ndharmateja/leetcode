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

    // Two ptr solution but with prev and curr
    private ListNode solution2(ListNode head, int k) {
        // Move advance 'k' steps forward
        // so that we can maintain a difference of 'k' nodes
        // between curr and advance
        ListNode advance = head;
        for (int i = 0; i < k; i++)
            advance = advance.next;

        // At this point if advance is null, it means that the head node
        // is the one that needs to be deleted as this happens only when k = size
        if (advance == null)
            return head.next;

        // Now that the difference between curr and advance is exactly k nodes
        // we can move them in tandem such that by the time
        // advance reaches null, curr would exactly reach the
        // node that we need to delete
        // So we would keep track of a prev pointer which points to the node
        // just before the curr node
        ListNode prev = null, curr = head;
        while (advance != null) {
            advance = advance.next;
            prev = curr;
            curr = curr.next;
        }

        // curr points to the node which we need to delete
        // so we delete it
        // prev won't be null as we already handled the case where the head needs to be
        // deleted
        // and the head would still remain same
        // because we already handled the case where head needs to be deleted
        prev.next = curr.next;
        return head;
    }

    private ListNode solution3(ListNode head, int n) {
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
        return solution3(head, n);
    }
}