// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution
{
private:
    // This is the solution corresponding the illustration.jpg
    // But this is not a correct solution as it has a flaw
    // During the second pass, once the random ptr of a node (say node A)
    // from the original list has been updated, any future node from the copy
    // list can't access the random that was originally stored in node A
    Node *solution1(Node *head)
    {
        // If list is empty, nothing to copy
        if (!head)
            return head;

        // curr ptr traverses the original list
        Node *curr_original{head};

        // Dummy sentinel node to add the new nodes created
        Node dummy{0};
        Node *tail{&dummy};

        // Iterate over each node in the original list
        while (curr_original)
        {
            // Create a new node and add it to the end of the list
            Node *node = new Node{curr_original->val};
            tail->next = node;
            tail = tail->next;

            //
            node->random = curr_original->random;
            curr_original->random = node;

            //
            curr_original = curr_original->next;
        }

        // Iterate over the copied list and update the pointers
        curr_original = head;
        Node *curr_copy = dummy.next;
        while (curr_copy)
        {
            Node *random_from_original_list = curr_copy->random;
            if (curr_copy->random)
                curr_copy->random = curr_copy->random->random;
            curr_original->random = random_from_original_list;

            // Update the pointers
            curr_original = curr_original->next;
            curr_copy = curr_copy->next;
        }

        // Return the new head
        return dummy.next;
    }

    // Theta(N) time and Theta(1) space solution
    // Idea:
    // Original list: A -> B -> C -> D ->
    // Create copy list interwoven: A -> A' -> B -> B' -> C -> C' -> D -> D' ->
    // So now setting the random ptrs of the copied list is easy as they are
    // right next to the original random ptrs. For eg, If A.random points to D
    // A' should point to D', we can get D' easily as it is next to D
    Node *solution2(Node *head)
    {
        // If list is empty, nothing to copy
        if (!head)
            return head;

        // Pass 1: Create the interwoven list with the copied list
        Node *curr{head};
        while (curr)
        {
            // Create new node and insert it after curr
            Node *node = new Node(curr->val);
            node->next = curr->next;
            curr->next = node;

            // Update curr
            // It is curr->next->next as we just inserted a new node next to it
            // This won't throw an error as we just inserted a new node after curr
            curr = curr->next->next;
        }

        // State: A -> A' -> B -> B' -> C -> C' -> D -> D' ->
        // Pass 2: Update the random pointers of the copied list
        // Iterate over the nodes of the original list
        // We only need to iterate until the second last node (the last
        // node from the original list)

        // We need to check curr != nullptr as well because we are jumping two nodes
        // in each iteration.
        // When curr is the second to last node, it will enter the loop
        // and then curr becomes null, and checking curr->next directly will
        // throw an error
        curr = head;
        while (curr && curr->next)
        {
            // Update the random pointer of the copied node
            // The copied node is next to the curr node
            // If the original node's next is nullptr, then the copied node's
            // random also has to be nullptr
            curr->next->random = curr->random ? curr->random->next : curr->random;

            // Update curr
            // This won't throw an error as we have an even lengthed list
            curr = curr->next->next;
        }

        // Pass 3: Remove the interleaving of the nodes
        // Iterate over the nodes of the original list

        // We need to check curr != nullptr as well because we are jumping two nodes
        // in each iteration.
        // When curr is the second to last node, it will enter the loop
        // and then curr becomes null, and checking curr->next directly will
        // throw an error
        Node *copy_head = head->next;
        curr = head;
        while (curr && curr->next)
        {
            Node *copy_curr = curr->next;
            curr->next = curr->next->next;
            copy_curr->next = copy_curr->next ? copy_curr->next->next : copy_curr->next;

            // Update curr
            // We don't need to do curr->next->next as we already updated the next
            // of the node in the original list to point to its original next
            curr = curr->next;
        }

        // Return
        return copy_head;
    }

public:
    Node *copyRandomList(Node *head) { return solution2(head); }
};