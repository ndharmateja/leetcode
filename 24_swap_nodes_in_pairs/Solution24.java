class Solution24 {
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

    public ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode newHead = head.next;

        ListNode prev = null;
        ListNode curr = head;
        ListNode next = head.next;

        while (true) {
            if (prev != null)
                prev.next = next;
            curr.next = next.next;
            next.next = curr;

            prev = curr;

            if (curr.next == null)
                break;
            curr = curr.next;

            if (curr.next == null)
                break;
            next = curr.next;
        }

        return newHead;
    }
}