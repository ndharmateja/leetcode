import java.util.HashSet;
import java.util.Set;

@SuppressWarnings("unused")
public class Solution141 {
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public boolean hasCycle(ListNode head) {
        return solution2(head);
    }

    // O(n) time and O(1) space
    // Reference: https://youtu.be/gBTe7lFR3vc?t=225
    // floyd's Tortoise and Hare
    // Using two pointers
    // Proof (that slow and fast have to come to same node eventually):
    // At some point both 'slow' and 'fast' pointers
    // are going to be in the cycle (if it exists)
    // let the 'slow' pointer be ahead of 'fast' by 'n' nodes
    // After one iteration, 'slow' will move by 1 and 'fast' will move by 2
    // => 'slow' will be ahead of 'fast' by n + 1 - 2 = 'n - 1' nodes
    // So after 'n' iterations, they both point to the same node
    // So even if 'slow' is ahead of 'fast' by 'n' nodes, it still runs in O(n)
    private boolean solution2(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (fast == slow)
                return true;
        }
        return false;
    }

    // O(n) time and O(n) space
    // Using hash set
    private boolean solution1(ListNode head) {
        Set<ListNode> set = new HashSet<>();
        while (head != null) {
            if (set.contains(head))
                return true;
            set.add(head);
            head = head.next;
        }
        return false;
    }

}