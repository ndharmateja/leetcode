class Solution2095 {
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

    public ListNode deleteMiddle(ListNode head) {
        if (head.next == null) {
            return null;
        }

        ListNode firstPrev = null;
        ListNode first = head;
        ListNode second = head;

        while (second != null && second.next != null) {
            firstPrev = first;
            first = first.next;
            second = second.next.next;
        }

        firstPrev.next = first.next;

        return head;
    }
}