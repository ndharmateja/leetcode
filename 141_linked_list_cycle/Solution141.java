import java.util.HashSet;
import java.util.Set;

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
        return solution1(head);
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