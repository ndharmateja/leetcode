class Solution {
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

    public int getDecimalValue(ListNode head) {
        int value = 0;

        // a(x^3) + b(x^2) + c(x^1) + d(x^0)
        // can be computed as
        // val = 0
        // Each step we do val = (val * x) + ai
        // a
        // a(x) + b
        // a(x^2) + b(x^1) + c
        // a(x^3) + b(x^2) + c(x^1) + d(x^0)
        ListNode curr = head;
        while (curr != null) {
            value = (value * 2) + curr.val;
            curr = curr.next;
        }

        return value;
    }
}