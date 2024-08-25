class Solution143 {
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

        @Override
        public String toString() {
            return "ListNode [val=" + val + "]";
        }
    }

    private ListNode reverseList(ListNode head) {
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

    // O(n) time
    // Method:
    // 1. Use fast and slow pointers to find middle of list
    // 2. Reverse second half of list
    // 3. Now add one element from first half and one element
    // from the reversed second half till both are done
    public void reorderList(ListNode head) {
        if (head == null || head.next == null || head.next.next == null) {
            return;
        }
        ListNode prev = null;
        ListNode first = head;
        ListNode second = head;

        while (second != null && second.next != null) {
            prev = first;
            first = first.next;
            second = second.next.next;
        }
        // Removes connection from first half to second half
        prev.next = null;

        // Reverse second half of list
        first = reverseList(first);

        // Add node from left half to newly building list
        ListNode curr = head;

        // 2 pointers for iterating two halfs
        ListNode curr1 = head.next;
        ListNode curr2 = first;

        // boolean for indicating which half to add node from
        boolean fromFirst = false;

        // iterate till both are non empty
        while (curr1 != null && curr2 != null) {
            if (fromFirst) {
                curr.next = curr1;
                curr = curr.next;
                curr1 = curr1.next;
            } else {
                curr.next = curr2;
                curr = curr.next;
                curr2 = curr2.next;
            }
            fromFirst = !fromFirst;
        }

        // Add any leftover node
        if (curr1 != null)
            curr.next = curr1;
        if (curr2 != null)
            curr.next = curr2;
    }
}