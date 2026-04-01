/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

public:
    // Theta(N) time and Theta(1) space
    // the time is Theta(N) because we either reach the end
    // or we go through the whole list atleast once
    bool hasCycle(ListNode *head)
    {
        // If no elements or one element pointing to null, no cycle
        if (!head || !head->next)
            return false;

        // Using slow and fast pointers
        ListNode *slow = head, *fast = head;

        // We should check both fast and fast->next to handle both
        // even and odd lengthed lists
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            // If the slow and fast pointers become same again, it means there is a cycle
            // If the pointers are same, it means that the objects
            // they are pointing to are the same, which means they are the same node
            if (slow == fast)
                return true;
        }

        // If we reach here, it means that we reached the end so no cycle
        return false;
    }
};