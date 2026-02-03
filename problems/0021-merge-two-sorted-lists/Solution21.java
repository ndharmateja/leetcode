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

    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        return solution2(list1, list2);
    }

    private ListNode solution1(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode();
        ListNode tail = dummy;

        ListNode curr1 = list1;
        ListNode curr2 = list2;

        while (curr1 != null && curr2 != null) {
            if (curr1.val < curr2.val) {
                tail = addNext(tail, curr1);
                curr1 = curr1.next;
            } else {
                tail = addNext(tail, curr2);
                curr2 = curr2.next;
            }
        }

        // Attach the remaining lists if not empty
        if (curr1 != null)
            tail = addNext(tail, curr1);
        if (curr2 != null)
            tail = addNext(tail, curr2);

        return dummy.next;
    }

    private static ListNode addNext(ListNode to, ListNode next) {
        to.next = next;
        return next;
    }

    // Recursive solution
    private ListNode solution2(ListNode list1, ListNode list2) {
        if (list1 == null)
            return list2;
        if (list2 == null)
            return list1;

        ListNode head;
        if (list1.val < list2.val) {
            head = list1;
            head.next = mergeTwoLists(list1.next, list2);
        } else {
            head = list2;
            head.next = mergeTwoLists(list1, list2.next);
        }
        return head;
    }
}
