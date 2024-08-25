class Solution92 {
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

    public ListNode reverseBetween(ListNode head, int left, int right) {
        // Sentinel node
        ListNode dummy = new ListNode();
        dummy.next = head;

        // Get node at left-1 index
        ListNode preLeft = dummy;
        for (int i = 0; i < left - 1; i++) {
            preLeft = preLeft.next;
        }

        // Get node at right+1 index (could be null)
        // 1 + (right - left) + 1
        // 1 => to go to left
        // (right - left) => to go to right
        // 1 => to go one after right
        ListNode postRight = preLeft;
        for (int i = 0; i < 1 + (right - left) + 1; i++) {
            postRight = postRight.next;
        }

        // Reverse pointers moving from left to right
        ListNode prev = preLeft;
        ListNode curr = preLeft.next;
        while (curr != postRight) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        // Reassign end pointers of the reversed part
        preLeft.next.next = postRight;
        preLeft.next = prev;

        // Return new head
        return dummy.next;
    }
}