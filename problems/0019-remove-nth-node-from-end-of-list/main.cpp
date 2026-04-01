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

    static int get_size(ListNode *head)
    {
        int size = 0;
        while (head)
        {
            ++size;
            head = head->next;
        }
        return size;
    }

    /**
     * Assumes that 1 <= k <= size (Leetcode constraint)
     * Theta(N + (N - k)) running time and Theta(1) space
     * We are doing one pass to find the size
     * and a second partial pass to go until the node to delete
     */
    static ListNode *solution1(ListNode *head, int k)
    {
        // Find the number of elements in the list
        int size = get_size(head);

        // If k == size, it means we need to remove the head
        if (k == size)
            return head->next;

        // The index of the node to be deleted = size - k
        // So we get to the node at index size-k-1 and update its pointer
        // To get to a node at index 'p' we need to make 'p' jumps from the head
        // So we need to run the loop size - k - 1 times
        ListNode *curr = head;
        for (int i = 0; i < size - k - 1; i++)
            curr = curr->next;

        // This works even if k=1 => the last node needs to be deleted
        // because we stop curr at one node prior, so curr->next will never be nullptr
        curr->next = curr->next->next;
        return head;
    }

    // Theta(N) and Theta(1) solution
    // Better than solution1 as it essentially does only one pass
    ListNode *solution2(ListNode *head, int k)
    {
        // Eg: list is A -> B -> C -> D -> E -> F -> G -> H -> I ->
        // and k = 3 => node to be deleted is G
        // First we make right jump 3 times from head, right would point to D
        // At this point left points to A and right points to D
        // We move both of them in unison until right reaches the last node
        // So left points to F and right points to I
        // Now the node to be deleted is F's next node

        // Move right ptr 'k' steps forward
        ListNode *right{head};
        for (int i = 0; i < k; i++)
            right = right->next;

        // If right at this point is nullptr, it means that k = size
        // which means that we need to delete the head itself
        if (!right)
            return head->next;

        // Start left at head and move both left and right in unison
        // until right reaches the last node
        // So that the offset of 'k' nodes remains between the left
        // and right pointers
        // Then the node to be deleted is left->next
        ListNode *left{head};
        while (right->next)
        {
            left = left->next;
            right = right->next;
        }

        // Remove node after left
        // left->next will never be null as even if k were to be 1
        // right would point to the last node
        // and left would stop at the second to last node
        left->next = left->next->next;
        return head;
    }

public:
    ListNode *removeNthFromEnd(ListNode *head, int k) { return solution2(head, k); }
};