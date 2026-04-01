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
    // O(N + M) time and Theta(1) space
    ListNode *solution1(ListNode *list1, ListNode *list2)
    {
        // If one of them is null return the other
        // It also handles the case of both being null (first if gets executed)
        if (!list1)
            return list2;
        if (!list2)
            return list1;

        // Create a dummy sentinel node for storing the resulting linked list
        // We are creating the dummy node on the stack instead of the heap,
        // so lesser overhead (heap creation and also manual deletion)
        ListNode dummy{};
        ListNode *tail = &dummy;
        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;

            // We don't need to explicitly set the tail's next to null
            // as at the start of each iteration (and even after the loop)
            // we are setting the tail's next
            // tail->next = nullptr;
        }

        // At this point, we'd have reached the end of one of the lists
        // So we can attach the remaining list
        tail->next = list1 ? list1 : list2;

        // Return the head of the merged list
        return dummy.next;
    }

public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) { return solution1(list1, list2); }
};