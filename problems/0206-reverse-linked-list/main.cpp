/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    // Iterative solution
    // Theta(N) time and Theta(1) space
    ListNode *solution1(ListNode *head)
    {
        // If list is empty or has one element, nothing to reverse
        if (!head || !head->next)
            return head;

        // Iterate through the list and reverse the pointer of each node
        ListNode *prev = nullptr, *curr = head;
        while (curr)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // prev at this point points to the last node in the list
        // which is the new head
        return prev;
    }

    // Recursive solution
    // Theta(N) time and Theta(N) space (recursion)
    ListNode *solution2(ListNode *head)
    {
        // Base cases
        // If list is empty or has one element, nothing to reverse
        if (!head || !head->next)
            return head;

        // A -> B -> C -> D ->
        // first we can reverse B -> C -> D -> to get D -> C -> B -> recursively
        // and then we can add A at the end (next to the old head - B)
        // After the recursive call, head (A) still points to B (which is the last node)
        // So we can make B point to A by doing head->next->next = head
        // and then make the last node A (head)'s next to null
        ListNode *newHead = solution2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }

public:
    ListNode *reverseList(ListNode *head) { return solution2(head); }
};