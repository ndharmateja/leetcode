public class Solution142 {
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    // O(n) time and O(1) space
    // Reference: https://youtu.be/wjYnzkAhcNk?t=375
    // Floyd's Algorithm
    // Method:
    // 1. Use fast and slow pointers to detect if cycle exists
    // 2. If fast reaches end, => no cycle
    // 3. fast and slow become equal at some node
    // 4. From that node, the start of cycle is at the same distance
    // from the head of the linked list
    // 5. So we can start another slow pointer at the head and move the slow2
    // pointer and the slow pointer (where fast and slow met) by one node
    // to eventually meet up at the start of the cycle
    public ListNode detectCycle(ListNode head) {
        ListNode slow = head, fast = head;

        boolean foundCycle = false;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (fast == slow) {
                foundCycle = true;
                break;
            }
        }

        if (!foundCycle)
            return null;

        ListNode slow2 = head;
        while (slow != slow2) {
            slow = slow.next;
            slow2 = slow2.next;
        }

        return slow2;
    }
}