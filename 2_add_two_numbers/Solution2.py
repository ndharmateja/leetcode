from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
class Solution2:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        carry = 0
        prev = None
        curr = ListNode(-1)
        head = curr

        while l1 is not None and l2 is not None:
            total = l1.val + l2.val + carry
            carry = total // 10
            curr.val = total % 10

            curr.next = ListNode(-1)

            prev = curr
            curr = curr.next
            l1 = l1.next
            l2 = l2.next

        while l1 is not None:
            total = l1.val + carry
            carry = total // 10
            curr.val = total % 10

            curr.next = ListNode(-1)

            prev = curr
            curr = curr.next
            l1 = l1.next

        while l2 is not None:
            total = l2.val + carry
            carry = total // 10
            curr.val = total % 10

            curr.next = ListNode(-1)

            prev = curr
            curr = curr.next
            l2 = l2.next


        if carry != 0:
            curr.val = carry
        else:
            prev.next = None

        return head