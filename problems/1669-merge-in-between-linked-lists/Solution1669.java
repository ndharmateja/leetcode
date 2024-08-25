class Solution1669 {
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

    public ListNode mergeInBetween(ListNode list1, int a, int b, ListNode list2) {
        // After the iterations
        // prev will contain the node before the ath node
        // and curr will contain the bth node
        ListNode prev = null;
        ListNode curr = list1;
        for (int i = 0; i < a; i++) {
            prev = curr;
            curr = curr.next;
        }
        for (int i = 0; i < b - a; i++) {
            curr = curr.next;
        }

        // Get the end of list2
        ListNode list2End = list2;
        while (list2End.next != null) {
            list2End = list2End.next;
        }

        // Connect prev to the start of list2
        // and list2's end to curr.next
        prev.next = list2;
        list2End.next = curr.next;

        return list1;
    }
}