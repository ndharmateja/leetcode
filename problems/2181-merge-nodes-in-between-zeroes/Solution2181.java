class Solution2181 {
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

    // The next node of 'curr' will contain zero
    // and will not be null
    //
    // eg: curr -> 0 -> 1 -> 2 -> 3 -> 0 -> 17 -> ...
    // after process method runs, it will become
    // 6 -> 0 -> 17 -> ...
    // and will return the new node with '6'
    private ListNode process(ListNode curr) {
        // If the '0' node is the end of the list
        // we return null
        if (curr.next.next == null) {
            return null;
        }

        // Calculate the sum of all the nodes
        // until we reach the next '0'
        int sum = 0;
        curr = curr.next.next;
        while (curr.val != 0) {
            sum += curr.val;
            curr = curr.next;
        }

        // next for the newNode will be curr
        // as it should point to the next zero node
        ListNode newNode = new ListNode(sum, curr);
        return newNode;
    }

    // O(n) time and O(1) space solution
    public ListNode mergeNodes(ListNode head) {
        ListNode dummy = new ListNode();
        dummy.next = head;

        // Each iteration, we process the list of nodes
        // starting from '0'
        // The node next to 'curr' will be a zero node
        // and the function returns a new node with sum total
        // of all the nodes between zeroes
        // and also the new node points to the next zero node
        ListNode curr = dummy;
        while (curr != null) {
            // curr's next will be the new node
            // (which points to the next zero)
            curr.next = process(curr);

            // curr will be the new node
            // and will point to the next zero node
            curr = curr.next;
        }

        return dummy.next;
    }
}