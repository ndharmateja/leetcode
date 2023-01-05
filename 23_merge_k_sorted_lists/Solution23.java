@SuppressWarnings("unused")
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

    // O(n log k) time
    // Reference: https://www.youtube.com/watch?v=q5a5OiGbT6Q&t=453s
    // Idea: Merge pairs of linked lists
    // Eg: 4 lists [l1, l2, l3, l4]
    // Merge l1 and l2, l3 and l4 => [l5, l6]
    // Merge l5 and l6 => [l7]
    private ListNode solution2(ListNode[] lists) {
        if (lists.length == 0)
            return null;
        while (lists.length > 1) {
            ListNode[] mergedLists = new ListNode[(lists.length + 1) / 2];
            for (int i = 0; i < mergedLists.length; i++) {
                mergedLists[i] = mergeTwoLists(lists[2 * i], 2 * i + 1 < lists.length ? lists[2 * i + 1] : null);
            }
            lists = mergedLists;
        }
        return lists[0];
    }

    // O(nk log(nk)) time
    // Idea: Join all lists into a single list and apply
    // sorting on that
    private ListNode solution3(ListNode[] lists) {
        return null;
    }

    // O(nk log(nk)) time
    // Reference: https://www.youtube.com/watch?v=kpCesr9VXDA
    // Idea: Use min-heap
    private ListNode solution4(ListNode[] lists) {
        return null;
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