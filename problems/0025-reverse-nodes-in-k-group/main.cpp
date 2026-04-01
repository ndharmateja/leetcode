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

    static ListNode *reverse_list(ListNode *head)
    {
        // If list is empty or has one element, nothing to reverse
        if (!head || !head->next)
            return head;

        // Iterate through the list and reverse the pointer of each node
        ListNode *prev{nullptr}, *curr{head};
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

    /**
     * Function that reverses the first 'k' nodes of the list
     * and returns the new head of the list.
     * If there are less than 'k' nodes in the given list then
     * no reversing happens and the original head itself is returned
     * with the list unmodified
     */
    static ListNode *reverse_one_k_group(ListNode *head, int k)
    {
        // Run a loop for 'k' times and reverse the pointer of each node
        ListNode *curr{head}, *prev{nullptr};
        for (int i = 0; i < k; i++)
        {
            // If there aren't enough nodes, curr becomes null before reaching the
            // end of the k iterations
            // In which case the reversal must be undoed
            // if we were reversing A -> B -> C ->  and k = 4
            // At the point curr becomes null the list is C -> B -> A ->
            // with curr=null and prev pointing to C
            // So we can just reverse the list and return. It would essentially be
            // returning the list in the state the function received it in
            if (!curr)
                return reverse_list(prev);

            // Reverse the pointer of the curr node to point to prev
            // and update the pointers
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // At this point curr points to the (k+1)th node from the start (could be null
        // if exactly k nodes are present in the list starting at head)
        // So the original head which becomes the last node of the reversed group
        // should point to the (k+1)th node after the reversal
        head->next = curr;

        // prev is the head of the reversed part
        return prev;
    }

public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        // If k is 1, then the reversed list is same as the original
        // If 0 or 1 nodes in the list, nothing to reverse
        if (k == 1 || !head || !head->next)
            return head;

        // We run this loop as long as curr != nullptr
        // If curr becomes null in the loop check, it means that the total number
        // of nodes in the list is exactly a multiple of 'k' which is why
        // curr which is the head of a group became null
        ListNode dummy{};
        ListNode *prev_group_tail{&dummy};
        ListNode *curr{head};
        while (curr)
        {
            // Reverse one group of 'k' nodes starting at curr
            // Prev group's tail should point to the new head returned by the function
            prev_group_tail->next = reverse_one_k_group(curr, k);

            // If there aren't k nodes left and the reversal didn't happen
            // If prev group's tail is pointing to curr itself, it means that the
            // reversal didn't happen, in which case we know that this is the last group
            // and there is no more work left to do
            if (curr == prev_group_tail->next)
                break;

            // If the reversal happened, update pointers for the next iteration
            // The curr (head of the group before reversal) becomes the last node of the group
            // So this node has to become the prev group's tail for the next iteration
            // and the node after it becomes the head of the next group
            prev_group_tail = curr;
            curr = curr->next;
        }

        // return the new head of the list
        return dummy.next;
    }
};