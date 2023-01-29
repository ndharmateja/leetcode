import java.util.Random;

class Solution382 {
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

    ListNode head;
    int size;
    Random random;

    public Solution382(ListNode head) {
        this.head = head;
        computeListSize();
        this.random = new Random();
    }

    private void computeListSize() {
        ListNode curr = this.head;
        this.size = 0;
        while (curr != null) {
            this.size++;
            curr = curr.next;
        }
    }

    public int getRandom() {
        int nodeIndex = this.random.nextInt(this.size);

        ListNode curr = this.head;
        for (int i = 0; i < nodeIndex; i++) {
            curr = curr.next;
        }

        return curr.val;
    }
}