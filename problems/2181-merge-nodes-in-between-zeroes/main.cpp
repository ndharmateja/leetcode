#include <utility>

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

    /**
     * Merges the values from the head to the first 0 into one
     * node containing the sum of all the merged nodes and this node
     * points to the node after the zero node
     * Assumes that there is atleast one non-zero node before the zero node
     * Also assumes that a zero node exists.
     *
     * Eg: 3 -> 4 -> 5 -> 0 -> 1 -> 2 -> 3 -> 4 -> 0 -> -4 -> ...
     * will be made into (3 + 4 + 5) -> 1 -> 2 -> 3 -> 4 -> 0 -> -4 ...
     * 12 -> 1 -> 2 -> 3 -> 4 -> 0 -> ...
     */
    static void merge_one_group(ListNode *head)
    {
        // Loop until we get a zero value and store the sum in the head node
        ListNode *curr = head->next;
        while (curr->val)
        {
            head->val += curr->val;
            curr = curr->next;
        }

        // At this point, curr points to the 0 node
        head->next = curr->next;
    }

    /**
     * This solution doesn't create any new nodes and stores the
     * sum of a merged group in the head of the group (node after the 0)
     * and the pointers are adjusted accordingly.
     * If the original list is not to be mutated or if memory leaks (all the
     * other nodes and zero nodes still exist in memory) is an issue
     * use solution 2
     */
    static ListNode *solution1(ListNode *head)
    {
        // Start from the first non-zero node and merge each group
        // contained between zeros
        // Once a group is merged, we go to the next node and do the merge
        // again until all groups are merged
        ListNode *curr = head->next;
        while (curr)
        {
            merge_one_group(curr);
            curr = curr->next;
        }
        return head->next;
    }

    /**
     * Merges the values from the head to the first 0 into one
     * node containing the sum of all the merged nodes and this node
     * is returned without modifying the original list
     * Assumes that there is atleast one non-zero node before the zero node
     * Also assumes that a zero node exists.
     *
     * Returns a pair of pointers:
     * 1. the pointer to the newly created node
     * 2. the pointer to the head of the next group
     *
     * Eg: 3 -> 4 -> 5 -> 0 -> 1 -> 2 -> 3 -> 4 -> 0 -> -4 -> ...
     * will be made into (3 + 4 + 5) -> 1 -> 2 -> 3 -> 4 -> 0 -> -4 ...
     * 12 -> 1 -> 2 -> 3 -> 4 -> 0 -> ...
     */
    static std::pair<ListNode *, ListNode *> merge_one_group_and_create_new_node(const ListNode *head)
    {
        int sum{0};
        ListNode *curr = head->next;
        while (curr->val)
        {
            sum += curr->val;
            curr = curr->next;
        }

        return {new ListNode(sum), curr->next};
    }
    static ListNode *solution2(const ListNode *head)
    {
        ListNode dummy{};
        ListNode *tail{&dummy}, *curr{head->next};
        while (curr)
        {
            auto result = merge_one_group_and_create_new_node(curr);
            tail->next = result.first;
            tail = tail->next;
            curr = result.second;
        }
        return dummy.next;
    }

public:
    ListNode *mergeNodes(ListNode *head) { return solution2(head); }
};