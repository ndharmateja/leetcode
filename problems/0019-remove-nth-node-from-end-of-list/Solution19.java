@SuppressWarnings("unused")
class Solution19 {
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

    // Use two pointers
    // Advance first pointer 'n+1' times ahead (If it reaches null midway
    // it means that we have to delete the head)
    // Second pointer will still be at head
    // Now move both pointers one by one till first pointer reaches null
    // Remove the node after the second pointer
    private ListNode solution1(ListNode head, int n) {
        ListNode advance = head;
        ListNode curr = head;

        for (int i = 0; i < n + 1; i++) {
            if (advance == null) {
                return head.next;
            }
            advance = advance.next;
        }

        while (advance != null) {
            advance = advance.next;
            curr = curr.next;
        }

        curr.next = curr.next.next;

        return head;
    }

    // Two ptr solution but with prev and curr
    private ListNode solution2(ListNode head, int k) {
        // Move advance 'k' steps forward
        // so that we can maintain a difference of 'k' nodes
        // between curr and advance
        ListNode advance = head;
        for (int i = 0; i < k; i++)
            advance = advance.next;

        // At this point if advance is null, it means that the head node
        // is the one that needs to be deleted as this happens only when k = size
        if (advance == null)
            return head.next;

        // Now that the difference between curr and advance is exactly k nodes
        // we can move them in tandem such that by the time
        // advance reaches null, curr would exactly reach the
        // node that we need to delete
        // So we would keep track of a prev pointer which points to the node
        // just before the curr node
        ListNode prev = null, curr = head;
        while (advance != null) {
            advance = advance.next;
            prev = curr;
            curr = curr.next;
        }

        // curr points to the node which we need to delete
        // so we delete it
        // prev won't be null as we already handled the case where the head needs to be
        // deleted
        // and the head would still remain same
        // because we already handled the case where head needs to be deleted
        prev.next = curr.next;
        return head;
    }

    private static int getSize(ListNode head) {
        int size = 0;
        while (head != null) {
            size++;
            head = head.next;
        }
        return size;
    }

    // Deletes the node at index 'index' and returns the new head
    // Assumes that index is valid => 0 <= index <= size-1
    // Assumes that head is not null
    private static ListNode deleteNode(ListNode head, int index) {
        // If head needs to be deleted
        if (index == 0)
            return head.next;

        // jump 'index-1' times to reach the node that precedes
        // the node that we need to delete
        ListNode curr = head;
        for (int i = 0; i < index - 1; i++)
            curr = curr.next;

        // Delete the node after curr
        // Since the index is valid, curr.next (the node to delete) won't be null
        curr.next = curr.next.next;
        return head;
    }

    private ListNode solution3(ListNode head, int k) {
        // Get the size of the list
        int size = getSize(head);

        // Determine the index of the node to delete (from front 0-based)
        // k = 1 => index = size - 1
        // k = 2 => index = size - 2
        // ...
        // k = size - 1 => index = 1 (size - (size - 1))
        // k = size => index = 0 (size - (size))
        int index = size - k;

        // Delete the node in the list at that index
        // 1 <= k <= size (from the problem constraints)
        // that means that 0 <= i <= size-1
        // so the index will be valid
        return deleteNode(head, index);
    }

    public ListNode removeNthFromEnd(ListNode head, int n) {
        return solution3(head, n);
    }
}