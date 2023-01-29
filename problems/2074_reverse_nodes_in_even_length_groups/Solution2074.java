class Solution2074 {
    public class ListNode {
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

    // Reverses a set of nodes if k is even
    // Otherwise doesn't do anything
    // Returns the last node of the reversed/non-reversed list
    private ListNode process(ListNode startPrev, int k) {
        if (k % 2 == 0) {
            return reverseOneGroup(startPrev, k);
        } else {
            ListNode curr = startPrev;
            for (int i = 0; i < k; i++) {
                curr = curr.next;
            }
            return curr;
        }
    }

    // See Leet Code 25 for more information
    public ListNode reverseEvenLengthGroups(ListNode head) {
        ListNode dummy = new ListNode();
        dummy.next = head;

        int size = 0;
        ListNode curr = dummy.next;
        while (curr != null) {
            curr = curr.next;
            size++;
        }

        int numNodesProcessed = 0;
        int k = 1;
        curr = dummy;
        while (numNodesProcessed < size) {
            // to handle the last group if size < k
            k = Math.min(k, size - numNodesProcessed);
            curr = process(curr, k);
            numNodesProcessed += k++;
        }

        return dummy.next;
    }
}