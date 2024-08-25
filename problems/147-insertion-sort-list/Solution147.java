class Solution147 {
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

    // head is dummy
    // And also since we checked that it won't be inserted at the end
    // we don't need to take care of that
    private void insertAtSlot(ListNode head, ListNode node) {
        // Find node with value greater than equal to node
        // and insert the node before that
        ListNode prev = head; // since head is dummy, node won't be inserted before head
        ListNode curr = head.next;
        while (node.val > curr.val) {
            prev = curr;
            curr = curr.next;
        }

        // Insert node between prev and curr
        prev.next = node;
        node.next = curr;
    }

    public ListNode insertionSortList(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode dummy = new ListNode(-10000); // because min value of any node is -5000
        dummy.next = head;

        ListNode prev = dummy;
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            if (curr.val < prev.val) {
                // If the value of curr is less than prev
                // it means it has to be inserted somewhere
                // before prev
                // prev's next becomes next
                prev.next = next;
                insertAtSlot(dummy, curr);
            } else {
                // check if curr needs to be in its current slot
                // then no need to do any insertion
                // Just "prev" needs to be updated
                prev = curr;
            }
            curr = next;
        }

        return dummy.next;
    }
}