public class Solution25 {
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

    /**
     * Reverses 'k' nodes from startPrev.next
     * The first node after reversal will be new 'next'
     * of startPrev
     * And the last node's next after reversal will be
     * the old node next to the pre-reversed list
     * 
     * There will be atleast 'k' nodes after 'startPrev'
     * 
     * @param startPrev - The node before the start of the
     *                  'k' group that needs to be reversed
     * @param k
     * @return - the last node of the reversed group
     */
    private ListNode reverseOneGroup(ListNode startPrev, int k) {
        // To keep track of which node to return
        ListNode start = startPrev.next;

        // Iterate and reverse each pointer 'k' times
        ListNode prev = startPrev;
        ListNode curr = startPrev.next;
        for (int i = 0; i < k; i++) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        // Assign the new pointers
        // at the start and end of the list
        startPrev.next = prev;
        start.next = curr;

        // The last node after reversal
        // will be the 'start' node
        return start;
    }

    // O(n) time and O(1) space solution
    public ListNode reverseKGroup(ListNode head, int k) {
        // Sentinel node at the start
        ListNode dummy = new ListNode();
        dummy.next = head;

        // Find size of the linked list
        int size = 0;
        ListNode curr = head;
        while (curr != null) {
            size++;
            curr = curr.next;
        }

        // Reverse each group 'size / k' times
        curr = dummy;
        int numReversals = size / k;
        for (int i = 0; i < numReversals; i++) {
            curr = reverseOneGroup(curr, k);
        }

        // Return the new head
        return dummy.next;
    }

    public static void main(String[] args) {
        ListNode node1 = new ListNode(1);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(3);
        ListNode node4 = new ListNode(4);
        ListNode node5 = new ListNode(5);

        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;

        Solution25 s = new Solution25();
        s.reverseKGroup(node1, 2);
    }
}