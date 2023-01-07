public class Solution160 {
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    private int getListSize(ListNode head) {
        ListNode curr = head;
        int size = 0;
        while (curr != null) {
            size++;
            curr = curr.next;
        }
        return size;
    }

    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        int sizeA = getListSize(headA);
        int sizeB = getListSize(headB);

        // Move headA or headB such that
        // both of their heads are at the same distance
        // from their ends
        if (sizeA > sizeB) {
            for (int i = 0; i < sizeA - sizeB; i++) {
                headA = headA.next;
            }
        }
        if (sizeB > sizeA) {
            for (int i = 0; i < sizeB - sizeA; i++) {
                headB = headB.next;
            }
        }

        // Now the intersection can be found by moving
        // both nodes one at a time
        ListNode currA = headA;
        ListNode currB = headB;
        while (currA != null) {
            if (currA == currB)
                return currA;
            currA = currA.next;
            currB = currB.next;
        }

        return null;
    }
}