import java.util.Stack;

@SuppressWarnings("unused")
class Solution234 {
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

    public boolean isPalindrome(ListNode head) {
        return solution2(head);
    }

    // O(n) time and O(1) space solution
    // Reverse the first half of the list and
    // and compare it with the second half
    private boolean solution2(ListNode head) {
        if (head.next == null) {
            return true;
        }
        if (head.next.next == null) {
            return head.val == head.next.val;
        }
        ListNode prev = null;
        ListNode first = head;
        ListNode second = head;
        ListNode next = head.next;

        // Run two pointers (first and second)
        // to reach the middle of the list
        // while reversing the first half of the list
        while (second != null && second.next != null) {
            // Advance 2nd pointer twice
            second = second.next.next;

            next = first.next;
            first.next = prev;
            prev = first;
            first = next;
        }

        // for odd number list, skip middle value
        if (second != null) {
            first = first.next;
        }

        // From 'prev' and 'first' pointers
        // iterate till the end and if any values don't match
        // return false
        // From 'prev' we go backwards towards the start of the list
        // From 'first' we go forwards from the middle to the
        // end of the list
        while (prev != null) {
            if (prev.val != first.val) {
                return false;
            }
            prev = prev.next;
            first = first.next;
        }

        return true;

    }

    // O(n) time and O(n) space solution
    // First pass to find size
    // Put first half of list in stack
    // and pop each and compare while iterating over second
    // half of list
    private boolean solution1(ListNode head) {
        int size = 0;
        ListNode curr = head;
        while (curr != null) {
            curr = curr.next;
            size++;
        }
        if (size == 1) {
            return true;
        }

        Stack<Integer> stack = new Stack<>();
        curr = head;
        for (int i = 0; i < size / 2; i++) {
            stack.push(curr.val);
            curr = curr.next;
        }

        if (size % 2 != 0) {
            curr = curr.next;
        }

        for (int i = 0; i < size / 2; i++) {
            if (stack.pop() != curr.val)
                return false;
            curr = curr.next;
        }

        return true;
    }
}