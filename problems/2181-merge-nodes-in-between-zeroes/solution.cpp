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
    ListNode *mergeNodes(ListNode *head)
    {
        // No need to do any null checks or 1 node checks
        // as given constraint is that there would be atleast three nodes

        // A dummy sentinel node for adding the new non-duplicate nodes
        ListNode dummy;
        ListNode *tail_ptr = &dummy;

        // Iterate as long as there is a next node
        // as we don't need to process the last node as we know it would be a 0
        ListNode *curr = head;
        while (curr->next)
        {
            // At this point, curr's val can only be 0
            // As we either enter it here the first time
            // or we get here from continuing from the prev iteration
            // when curr reaches a zero node

            // Starting from the next node
            // add all the values until we reach the zero node again
            // storing the sum in the segment_start node
            ListNode *segment_start = curr;
            int sum = 0;
            curr = curr->next;
            while (curr->val)
            {
                sum += curr->val;
                curr = curr->next;
            }
            segment_start->val = sum;

            // At this point curr reached the next 0 node
            // So we can add the segment_start to the new list
            tail_ptr->next = segment_start;
            tail_ptr = tail_ptr->next;

            // We don't need to do curr = curr->next
            // as curr is at the next 0 node and we can go to the next iteration
        }
        // As we are not setting the next of the tail as nullptr each time
        // we have to do it at the end
        tail_ptr->next = nullptr;

        // Return head of the new list
        // We don't need to delete the dummy node as we created it on the stack
        return dummy.next;
    }
};