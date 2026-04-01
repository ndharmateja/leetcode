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

public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        // Create a dummy sentinel node to store the resulting list
        ListNode dummy{};
        ListNode *tail{&dummy};

        // Using unsigned chars as sum never exceeds 19 and carry never exceeds 1
        unsigned char sum{0}, carry{0};

        // Parallelly traverse both lists
        // If one of them reaches the end first, we can default to a value of 0
        while (l1 || l2)
        {
            // Get the current digits
            unsigned char digit1 = l1 ? l1->val : 0;
            unsigned char digit2 = l2 ? l2->val : 0;

            // sum can't cross 19, so we can get the last digit and carry
            // using subtraction instead of division and mod
            sum = digit1 + digit2 + carry;
            carry = (sum >= 10) ? 1 : 0;
            sum = (sum >= 10) ? (sum - 10) : sum;

            // Create the new node and add to the list
            ListNode *node = new ListNode{static_cast<int>(sum)};
            tail->next = node;
            tail = tail->next;

            // Move the pointers by one each
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }

        // At the end if carry still exists we have to add a extra node
        if (carry)
            tail->next = new ListNode{static_cast<int>(carry)};

        // Return the head
        return dummy.next;
    }
};