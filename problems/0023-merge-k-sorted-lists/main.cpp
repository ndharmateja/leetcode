#include <vector>
#include <queue>
#include <algorithm>

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

    static std::vector<ListNode *> filter_null_lists(std::vector<ListNode *> &lists)
    {
        // Filter out the empty lists
        std::vector<ListNode *> filtered_lists;
        std::copy_if(lists.begin(), lists.end(),
                     std::back_inserter(filtered_lists),
                     [](ListNode *l)
                     { return l != nullptr; });
        return filtered_lists;
    }

    /**
     * O(N + M) time and Theta(1) space
     */
    static ListNode *merge(ListNode *list1, ListNode *list2)
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

    static ListNode *merge_sort(ListNode *head)
    {
        // Base case: if 0 or 1 elements in the list, we can simply return
        if (!head || !head->next)
            return head;

        // Split the list into 2 halves and sort each recursively
        ListNode *right_head = split_list(head);
        head = merge_sort(head);
        right_head = merge_sort(right_head);

        // Merge the two sorted lists
        return merge(head, right_head);
    }

    struct NodeCompare
    {
        bool operator()(const ListNode *l1, const ListNode *l2) const { return l1->val > l2->val; }
    };

    /**
     * Min Heap solution
     * Theta(nk log n) time and Theta(n) space
     * where n = #lists, k - #nodes per list
     */
    static ListNode *solution1(std::vector<ListNode *> &lists)
    {
        std::vector<ListNode *> filtered_lists{filter_null_lists(lists)};

        // If the lists is empty or only has one list, we can exit early
        if (filtered_lists.empty())
            return nullptr;
        if (filtered_lists.size() == 1)
            return filtered_lists.at(0);

        // Min-heapify the vector of filtered lists
        std::priority_queue<ListNode *, std::vector<ListNode *>, NodeCompare>
            min_pq(filtered_lists.begin(), filtered_lists.end());

        // Create a sentinel node for the resulting list
        // This is created on the stack
        ListNode dummy{};
        ListNode *tail{&dummy};

        // Since we are doing an early exit when there is 0 or 1 list nodes in the vector
        // at this point, the min pq will have atleast 2 list nodes
        // As long as there are atleast 2 list nodes
        // in the pq, we take the smallest one among them
        // as each one of them is sorted. So the min among all the heads would be the next
        // entry in our resulting sorted list.
        // We add the popped node to the end of our resulting list
        // and its next node back to the pq
        while (min_pq.size() > 1)
        {
            // Remove the min node and append it to the new list
            ListNode *min{min_pq.top()};
            min_pq.pop();
            tail->next = min;
            tail = tail->next;

            // Add the next node back to the min pq if it is not null
            if (min->next)
                min_pq.push(min->next);
        }

        // At this point there is only one list node left in the pq
        // so we can directly append this whole list to the resulting list
        tail->next = min_pq.top();

        // Return the new list
        return dummy.next;
    }

    /**
     * Merge 2 lists at a time. so k lists become k/2 lists
     * and keep repeating that until we have one list left
     *
     * k = #lists, n = #nodes per list
     *
     * Running time for merge on two lists of size 'n' each = 2n
     *
     * Running time analysis (Assume that k is a power of 2, k = 2^m)
     * #merge-operations     work-per-merge-operation
     *  k/2 = 2^(m-1)                   2n
     *  k/4 = 2^(m-2)                   4n
     *  k/8 = 2^(m-3)                   8n
     *      .                           .
     *      .                           .
     *  2 = 2^(m-(m-1))             (2^(m-1))n
     *  1 = 2^(m-m)                   (2^m)n
     *
     * Work per level = (2^m)n = nk
     * #Levels = lg(k)
     * Total running time = nk * lgk
     *
     * Theta(nk lgk) time and Theta(1) space complexity
     */
    static ListNode *solution2(std::vector<ListNode *> &lists)
    {
        // Filter the null lists
        std::vector<ListNode *> filtered_lists{filter_null_lists(lists)};

        // If the lists is empty or only has one list, we can exit early
        if (filtered_lists.empty())
            return nullptr;
        if (filtered_lists.size() == 1)
            return filtered_lists.at(0);

        // Like bottom up merge sort
        // Merge starting with interval sizes of 1, 2, 4, ...
        // Each time we merge two intervals [lo, lo + sz - 1] and [lo + sz, lo + 2sz - 1]
        // We assume that the merged list of [lo, lo + sz - 1] is at lists[lo]
        // and that the merged list of [lo + sz, lo + 2sz - 1] is at lists[lo + sz]
        // and we put the resulting merged list of these two intervals in lists[lo] to
        // keep the invariant of storing the merged list at lo going.
        // Interval size starts at 1 and goes until it is less than k (keeps doubling)
        // For each interval size we keep going until there are atleast 2 intervals
        // the left interval of sz and the right interval of atleast 1
        // That is why we go until lo < k - sz
        int k(static_cast<int>(filtered_lists.size()));
        for (int sz = 1; sz < k; sz <<= 1)
        {
            for (int lo = 0; lo < k - sz; lo += (sz << 1))
                filtered_lists[lo] = merge(filtered_lists[lo], filtered_lists[lo + sz]);
        }
        return filtered_lists[0];
    }

    static ListNode *solution3(std::vector<ListNode *> &lists, int lo, int hi)
    {
        if (lo >= hi)
            return lists[lo];

        int mid = lo + (hi - lo) / 2;
        return merge(solution3(lists, lo, mid), solution3(lists, mid + 1, hi));
    }

    /**
     * Recursive version of solution2
     *
     * Theta(nk lgk) time and Theta(lg k) space complexity (for recursion)
     * where k = #lists, n = #nodes per list
     */
    static ListNode *solution3(std::vector<ListNode *> &lists)
    {
        // Filter the null lists
        std::vector<ListNode *> filtered_lists{filter_null_lists(lists)};

        // If the lists is empty or only has one list, we can exit early
        if (filtered_lists.empty())
            return nullptr;
        if (filtered_lists.size() == 1)
            return filtered_lists.at(0);

        return solution3(filtered_lists, 0, filtered_lists.size() - 1);
    }

    /**
     * Sorting the mega list solution
     * Creating the mega list - Theta(nk) time as we have to find the tail of each list
     * Sorting the mega list of nk elements: Theta(nk log nk)
     *
     * Theta(nk log(nk)) time and Theta(1) space
     * where k = #lists, n = #nodes per list
     */
    static ListNode *solution4(std::vector<ListNode *> &lists)
    {
        // Join all the lists
        ListNode dummy{};
        ListNode *tail(&dummy);
        for (ListNode *head : lists)
        {
            if (!head)
                continue;

            // Insert the head of the list at the end of the mega list
            tail->next = head;

            // Move the tail to the end of the list
            while (tail->next)
                tail = tail->next;
        }

        // Sort the mega list and return it
        return merge_sort(dummy.next);
    }

    /**
     * Keep accumulating each list one by one by merging with a
     * resulting list
     * where k = #lists, n = #nodes per list
     * Total running time: 2n + 3n + 4n + ... + kn = n(2 + 3 + ... + k) = n(k(k+1)/2 - 1)
     *
     * Theta(n(k^2)) running time and Theta(1) space complexity
     */
    static ListNode *solution5(std::vector<ListNode *> &lists)
    {
        // Filter the null lists
        std::vector<ListNode *> filtered_lists{filter_null_lists(lists)};

        // If the lists is empty or only has one list, we can exit early
        if (filtered_lists.empty())
            return nullptr;
        if (filtered_lists.size() == 1)
            return filtered_lists.at(0);

        // Go through each list starting from index 1 and merge it with
        // the list at index 0 (we keep accumulating the result in index 0)
        for (auto it = filtered_lists.begin() + 1; it != filtered_lists.end(); ++it)
            filtered_lists[0] = merge(filtered_lists[0], *it);

        // Return the merged iist that is at index 0
        return filtered_lists.at(0);
    }

    static int get_index_of_min_node(std::vector<ListNode *> &lists)
    {
        // leet code constraints: each value is between -10000 and 10000
        int min = 10001;
        int min_index = -1;
        int k{static_cast<int>(lists.size())};
        for (int i = 0; i < k; ++i)
        {
            ListNode *curr{lists[i]};
            if (!curr)
                continue;
            if (curr->val < min)
            {
                min = curr->val;
                min_index = i;
            }
        }

        // Return min index
        return min_index;
    }

    /**
     * Extend the idea of merging two lists.
     * Pick the minimum among all the k list nodes each time and add it to the resulting list
     * Theta(k * nk)=Theta(n(k^2)) time and Theta(1) space
     * where k = #lists, n = #nodes per list
     */
    static ListNode *solution6(std::vector<ListNode *> &lists)
    {
        // Filter the null lists
        std::vector<ListNode *> filtered_lists{filter_null_lists(lists)};

        // If the lists is empty or only has one list, we can exit early
        if (filtered_lists.empty())
            return nullptr;
        if (filtered_lists.size() == 1)
            return filtered_lists.at(0);

        // Dummy sentinel node for the new list
        ListNode dummy{};
        ListNode *tail{&dummy};
        int min_index;

        // Get the min node among all the lists each time
        // If the min_index is -1, it means that there are no more non null nodes left
        while ((min_index = get_index_of_min_node(lists)) != -1)
        {
            // Get the min most node among the n lists and add it to the resulting list
            ListNode *min_node = lists[min_index];
            tail->next = min_node;
            tail = tail->next;

            // Update the node at the min_index to its next as we just plucked it
            lists[min_index] = lists[min_index]->next;
        }

        // Return the new list
        return dummy.next;
    }

public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) { return solution6(lists); }
};