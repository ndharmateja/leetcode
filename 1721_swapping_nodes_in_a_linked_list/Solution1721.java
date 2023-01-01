/**
 * Definition for singly-linked list.
 */
class Solution1721 {
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

    // Solution with multiple passes
    // First pass to get size
    // and two more passes to get the corresponding two nodes
    // Then swap the values between those two nodes
    private ListNode solution1(ListNode head, int k) {
        int size = 0;
        ListNode curr = head;

        while (curr != null) {
            size++;
            curr = curr.next;
        }

        curr = head;
        for (int i = 0; i < k - 1; i++) {
            curr = curr.next;
        }
        ListNode node1 = curr;

        curr = head;
        for (int i = 0; i < (size - k + 1) - 1; i++) {
            curr = curr.next;
        }
        ListNode node2 = curr;

        int temp = node1.val;
        node1.val = node2.val;
        node2.val = temp;

        return head;
    }
    public ListNode swapNodes(ListNode head, int k) {
        return null;
    }
}