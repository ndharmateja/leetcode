class Solution61 {
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

    private int getListSize(ListNode head) {
        ListNode curr = head;
        int size = 0;
        while (curr != null) {
            size++;
            curr = curr.next;
        }
        return size;
    }

    public ListNode rotateRight(ListNode head, int k) {
        int size = getListSize(head);
        if (size <= 1)
            return head;

        // k can be more than size
        // so that is why do the % operator
        k = k % size;

        // To rotate the last 'k' elements
        // we need to track the firt 'size - k' elements
        // So we replace 'k' with 'size - k'
        k = size - k;

        // Create a sentinel node
        ListNode dummy = new ListNode();
        dummy.next = head;

        // Skip the first 'k' nodes
        ListNode curr = dummy;
        for (int i = 0; i < k; i++) {
            curr = curr.next;
        }

        // Assign the 'k+1'st node to dummy.next
        dummy.next = curr.next;
        // And curr has to be at the end
        // after the rotation
        curr.next = null;

        // Reach the end of the new list
        // and assign the old head as the next
        // to the last of the old list
        curr = dummy;
        while (curr.next != null) {
            curr = curr.next;
        }
        curr.next = head;

        // Return the new head after rotation
        return dummy.next;
    }
}