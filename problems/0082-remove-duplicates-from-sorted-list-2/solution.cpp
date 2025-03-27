struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode ext) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        // If list has only 0 or 1 nodes => no duplicates => nothing to remove
        if (head == nullptr || head->next == nullptr)
            return head;

        // A dummy sentinel node for adding the new non-duplicate nodes
        ListNode dummy;
        ListNode *tail_ptr = &dummy;

        ListNode *curr = head;
        while (curr != nullptr)
        {
            // If curr node is a duplicate
            // skip all nodes with that value
            int duplicate_value = curr->val;
            if (curr->next && curr->next->val == duplicate_value)
            {
                // Since curr and curr.next already have the same duplicate value
                // We can start looking from curr.next.next
                curr = curr->next->next;

                // As long as the curr node is not null (as there is a possibility of
                // reaching the end before we find a node with a different value)
                while (curr != nullptr && curr->val == duplicate_value)
                    curr = curr->next;

                // As soon as we reach the first node with a different value
                // we can go to the next iteration
                continue;
            }

            // If we reach here it means that we reached a node that is non-duplicate
            // So we add this node to the new list
            tail_ptr->next = curr;
            tail_ptr = tail_ptr->next;
            curr = curr->next;
        }
        // As we are not setting the next of the tail as nullptr each time
        // we have to do it at the end
        tail_ptr->next = nullptr;

        // Return head of the new list
        // We don't need to delete the dummy node as we created it on the stack
        return dummy.next;
    }
};