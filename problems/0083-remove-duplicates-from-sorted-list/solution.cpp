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
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *curr = head;
        while (curr != nullptr)
        {
            // As long as the next node's value is the same as
            // the current node's, delete the next node
            while (curr->next != nullptr && curr->val == curr->next->val)
            {
                curr->next = curr->next->next;
            }

            curr = curr->next;
        }

        // Return head as the head doesn't change
        return head;
    }
};