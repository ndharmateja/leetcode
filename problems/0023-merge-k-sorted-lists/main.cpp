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

    struct NodeCompare
    {
        bool operator()(const ListNode *l1, const ListNode *l2) const { return l1->val > l2->val; }
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
     * Min Heap solution
     * Theta(nk log n) time and Theta(n) space
     * where n = #lists, k - #nodes per list
     */
    ListNode *solution1(std::vector<ListNode *> &lists)
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
     * O(N + M) time and Theta(1) space
     */
    ListNode *merge(ListNode *list1, ListNode *list2)
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
     * Merge 2 lists at a time. so n lists become n/2 lists
     * and keep repeating that until we have one list left
     *
     * n = #lists, k - #nodes per list
     *
     * Running time for merge on two lists of size 'k' each = 2k
     *
     * Running time analysis (Assume that n is a power of 2, n = 2^m)
     * #merge-operations     work-per-merge-operation
     *  n/2 = 2^(m-1)                   2k
     *  n/4 = 2^(m-2)                   4k
     *  n/8 = 2^(m-3)                   8k
     *      .                           .
     *      .                           .
     *  2 = 2^(m-(m-1))             (2^(m-1))k
     *  2 = 2^(m-m)                   (2^m)k
     *
     * Work per level = (2^m)k = nk
     * #Levels = lgn
     * Total running time = nk * lgn
     *
     * Theta(nk lgn) time and Theta(1) space complexity
     */
    ListNode *solution2(std::vector<ListNode *> &lists)
    {
        return nullptr;
    }

    /**
     * Sorting the mega list solution
     * Creating the mega list - Theta(nk) time as we have to find the tail of each list
     * Sorting the mega list of nk elements: Theta(nk log nk)
     *
     * Theta(nk log(nk)) time and Theta(1) space
     * where n = #lists, k - #nodes per list
     */
    ListNode *solution3(std::vector<ListNode *> &lists) { return nullptr; }

    /**
     * Keep accumulating each list one by one by merging with a
     * resulting list
     * where n = #lists, k - #nodes per list
     * Total running time: 2k + 3k + 4k + ... + nk = k(2 + 3 + ... + n) = k(n(n+1)/2 - 1)
     *
     * Theta((n^2)k) running time and Theta(1) space complexity
     */
    ListNode *solution4(std::vector<ListNode *> &lists) { return nullptr; }

public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) { return solution2(lists); }
};