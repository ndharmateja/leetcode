class Solution23 {
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

    public ListNode mergeKLists(ListNode[] lists) {
        return solution1(lists);
    }

    // Merges two sorted lists and returns the head of the merged list
    private ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1 == null)
            return list2;
        if (list2 == null)
            return list1;

        // Iterate and insert the smaller list node
        // to current each time until both of them are
        // not empty
        ListNode dummy = new ListNode();
        ListNode curr = dummy;
        while (list1 != null && list2 != null) {
            if (list1.val <= list2.val) {
                curr.next = list1;
                curr = curr.next;
                list1 = list1.next;
            } else {
                curr.next = list2;
                curr = curr.next;
                list2 = list2.next;
            }
        }

        // Attach if any list is non empty
        if (list1 != null)
            curr.next = list1;
        if (list2 != null)
            curr.next = list2;

        // Return head
        return dummy.next;
    }

    // O(kn) time if each list is of size 'n'
    // Merge two lists at a time
    // and return the final merged list
    private ListNode solution1(ListNode[] lists) {
        if (lists.length == 0)
            return null;
        if (lists.length == 1)
            return lists[0];
        ListNode merged = lists[0];
        for (int i = 1; i < lists.length; i++) {
            merged = mergeTwoLists(merged, lists[i]);
        }
        return merged;
    }
}