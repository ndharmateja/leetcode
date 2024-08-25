class Solution328 {
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

    // O(n) time and O(1) space solution
    public ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null || head.next.next == null)
            return head;

        // Maintain two lists for odd and even index nodes
        ListNode head1 = head;
        ListNode curr1 = head1;

        ListNode head2 = head.next;
        ListNode curr2 = head2;

        // Add nodes from the main list alternatingly
        // to the two lists
        ListNode curr = head.next.next;
        boolean oddIndex = true;
        while (curr != null) {
            if (oddIndex) {
                curr1.next = curr;
                curr1 = curr1.next;
            } else {
                curr2.next = curr;
                curr2 = curr2.next;
            }

            oddIndex = !oddIndex;
            curr = curr.next;
        }

        // Connect end of first list to the second list
        // and make the end of second list as null
        curr1.next = head2;
        curr2.next = null;

        // return the new head
        return head1;
    }
}