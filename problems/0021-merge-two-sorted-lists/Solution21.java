@SuppressWarnings("unused")
public class Solution21 {
    private static class ListNode {
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

    private static ListNode addNext(ListNode to, ListNode next) {
        to.next = next;
        return next;
    }

    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode();
        ListNode curr = dummy;
        ListNode curr1 = list1;
        ListNode curr2 = list2;

        while (curr1 != null && curr2 != null) {
            if (curr1.val < curr2.val) {
                curr = addNext(curr, curr1);
                curr1 = curr1.next;
            } else {
                curr = addNext(curr, curr2);
                curr2 = curr2.next;
            }
        }

        // Attach the remaining lists if not empty
        if (curr1 != null)
            curr = addNext(curr, curr1);
        if (curr2 != null)
            curr = addNext(curr, curr2);

        return dummy.next;
    }
}
