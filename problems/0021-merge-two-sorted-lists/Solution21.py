from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution21:
    def mergeTwoLists(
        self, head1: Optional[ListNode], head2: Optional[ListNode]
    ) -> Optional[ListNode]:
        if head1 is None:
            return head2
        if head2 is None:
            return head1

        curr1, curr2 = head1, head2
        dummy: ListNode = ListNode()
        tail: ListNode = dummy

        while curr1 and curr2:
            if curr1.val <= curr2.val:
                tail.next = curr1
                curr1 = curr1.next
            else:
                tail.next = curr2
                curr2 = curr2.next
            tail = tail.next

        if curr1:
            tail.next = curr1
        if curr2:
            tail.next = curr2

        return dummy.next
