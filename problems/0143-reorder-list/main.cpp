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

    /**
     * @brief Splits the list into two halves and returns the head of the
     * right linked list. Assumes that there are atleast 2 nodes in the list.
     * If the number of total nodes is odd, the left list will have the
     * extra node.
     * @return Returns the head of the right linked list
     */
    static ListNode *split_list(ListNode *head)
    {
        // Use slow and fast pointers
        // If list is A -> B -> C -> D -> E ->
        // after the loop is done, slow will point to C and fast will point to E
        // If list is A -> B -> C -> D -> E -> F -> G -> H ->
        // after the loop is done, slow will point to D and fast will point to G
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // At this point slow points to the last node of the left list
        // So we sever the connection and return the head of the right list
        ListNode *right_head = slow->next;
        slow->next = nullptr;
        return right_head;
    }

    static ListNode *reverse_list(ListNode *head)
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

    /**
     * @brief Merges the two lists alternatively taking nodes from each list.
     * Starts with the left list. Only works if the #nodes in both the lists is same
     * or if the left list has one extra.
     */
    static void merge_lists(ListNode *left_head, ListNode *right_head)
    {
        // Iterate until right_head becomes null and alternatively take
        // a node from each list
        // Creating the dummy node on stack
        ListNode dummy{};
        ListNode *tail = &dummy;
        while (right_head)
        {
            // Take node from left list
            tail->next = left_head;
            tail = tail->next;
            left_head = left_head->next;

            // Take node from right list
            tail->next = right_head;
            tail = tail->next;
            right_head = right_head->next;
        }

        // At this point there could be one extra node from the left list
        // or it could be null
        tail->next = left_head;
    }

public:
    // Theta(N) time and Theta(1) space
    void reorderList(ListNode *head)
    {
        // If the list has 0 or 1 or 2 elements, there is nothing to reorder
        if (!head || !head->next || !head->next->next)
            return;

        // At this point we know that there are atleast 3 elements in the list
        ListNode *right_head = split_list(head);
        right_head = reverse_list(right_head);
        merge_lists(head, right_head);
    }
};