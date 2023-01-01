@SuppressWarnings("unused")
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

    // Get hold of two nodes in one pass
    private ListNode solution2(ListNode head, int k) {
        ListNode first = head;
        ListNode second = head;

        // to get the kth node from front
        // and also to maintain a gap of 'k' between first and second
        for (int i = 0; i < k - 1; i++) {
            second = second.next;
        }
        ListNode node2 = second;

        // Move both pointers by one each iteration
        // until the second reaches the last node
        // then the first node will be the kth node from back
        while (second.next != null) {
            first = first.next;
            second = second.next;
        }

        // Swap values
        int temp = first.val;
        first.val = node2.val;
        node2.val = temp;

        return head;
    }

    public ListNode swapNodes(ListNode head, int k) {
        return solution2(head, k);
    }

}