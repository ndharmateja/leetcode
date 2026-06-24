#include <vector>
#include <algorithm>
#include <unordered_set>
#include <deque>
#include <utility>

// Reference: https://github.com/ndharmateja/data-structures-cpp/blob/master/data-structures/priority-queues/index-min-pq/index_min_pq.hpp
// Removing type checking and error handling for leet code
// For more details and full code visit the above link
template <typename T>
class IndexMaxPQ
{
private:
    // Instance variables
    // pq[i]   => i is the heap index and pq[i] is the user specified index
    // Essentially pq is the heap array where in each index we are storing the
    // user index of the element instead of the actual element itself.
    //
    // qp[i]   => i is the user specified index and qp[i] is the heap index
    //            qp[i] is -1 if user didn't associate i with any element
    // keys[i] => i is the user specified index and keys[i] is the actual element
    // qp and keys are parallel arrays where i is the user specified index
    //     qp[i] holds the heap index and
    //     keys[i] holds the corresponding item
    //
    // Note that if the element at a user index i was removed from the pq, keys[i] need
    // not necessarily be empty. Since qp[i] is going to be -1 keys[i] is going to be
    // irrelevant.
    std::vector<int> qp;
    std::vector<T> keys;
    std::vector<int> pq;
    int n;
    int max_n;

    // Helper methods
    void swap(int i, int j)
    {
        // Swap elements at heap indices i and j
        std::swap(pq[i], pq[j]);

        // When we swap elements at heap indices i and j
        // we also need to swap indices pq[i] and pq[j] in the qp array
        // as the heap indices corresponding to the user indices have been changed
        int user_index_i{pq[i]}, user_index_j{pq[j]};
        std::swap(qp[user_index_i], qp[user_index_j]);
    }

    /**
     * This method returns a reference to the element and not a copy
     */
    const T &element_at(int heap_index) const
    {
        // The actual element for heap index i is keys[pq[i]]
        // pq[i] is the user index of the element at heap index i
        // and keys[pq[i]] is the actual element
        return keys[pq[heap_index]];
    }

    void swim(int i)
    {
        // i and p are the heap indices
        while (i > 0)
        {
            // We need to keep swapping as long as the parent < child
            int p = parent(i);

            // If element_at(p) >= element_at(i), we can break
            // (element_at(p) >= element_at(i)) <=> !(element_at(p) < element_at(i)) <=> !(element_at(i) > element_at(p))
            if (!(element_at(i) > element_at(p)))
                break;

            // Swap i with parent and update i
            swap(i, p);
            i = p;
        }
    }

    void sink(int i)
    {
        // Run the loop as long as there is a left child
        int to_swap;
        while ((to_swap = left_child(i)) < n)
        {
            // If the right child also exists and the right child element
            // is larger than the left child, then we need to swap ith element
            // with right child, so we increment to_swap index
            if (to_swap < n - 1 && element_at(to_swap + 1) > element_at(to_swap))
                to_swap++;

            // If the element at i greater than or equal than the larger child
            // then we don't need to swap
            // (element_at(i) >= element_at(to_swap)) <=> !(element_at(i) < element_at(to_swap)) <=> !(element_at(to_swap) > element_at(i))
            if (!(element_at(to_swap) > element_at(i)))
                break;

            // Swap with the larger child and update i
            swap(i, to_swap);
            i = to_swap;
        }
    }

    static int parent(int i) { return (i - 1) / 2; }
    static int left_child(int i) { return 2 * i + 1; };
    static int right_child(int i) { return 2 * i + 2; };

public:
    // Initialize (not reserve) the vectors with the given max_n
    IndexMaxPQ(int max_n) : qp(max_n, -1), keys(max_n), pq(max_n), n{0}, max_n{max_n} {}

    void insert(int k, T key)
    {
        // Insert the item at the end and swim
        qp[k] = n;
        keys[k] = key;
        pq[n] = k;
        n++;
        swim(n - 1);
    }

    void change(int k, T key)
    {
        // Change the item associated with index 'k'
        T old_key = keys[k];
        keys[k] = key;

        // swim/sink appropriately based on whether the value increased or decreased
        // If value is increased, then we only potentially need to swim as heap property
        // is potentially violated with the parent
        // Similarly we potentially need to sink otherwise
        int heap_index = qp[k];
        if (key > old_key)
            swim(heap_index);
        else
            sink(heap_index);
    }

    bool contains(int k) const { return qp[k] != -1; }

    void remove(int k)
    {
        // Get the index of the element in the heap
        int heap_index = qp[k];

        // Optimization: If the heap index itself is n-1, then we are deleting the
        // last node in the heap in which case no swimming or swapping needed
        if (heap_index == n - 1)
        {
            n--;
            qp[k] = -1;
            return;
        }

        // Get the keys that are being swapped
        // ! Get them before changing 'n' and swap
        // ! Make sure to type the variables as const T&, otherwise a copy construtor will be triggered
        const T &removed_key = element_at(heap_index);
        const T &last_element_key = element_at(n - 1);

        // Swap the element with the last element, decrement the n
        // and remove the given index 'k' from qp
        swap(heap_index, --n);
        qp[k] = -1;

        // ! The element we removed might be smaller or larger than the last element
        // So we swim or sink the index based on the value
        if (last_element_key > removed_key)
            swim(heap_index);
        else
            sink(heap_index);
    }

    T max() const { return element_at(0); }

    int max_index() const { return pq.front(); }

    int remove_max()
    {
        // Get the user index of the maximal element and remove it
        int user_index = pq[0];
        remove(user_index);
        return user_index;
    }

    bool empty() const { return !n; }
    int size() const { return n; }
};

class Solution
{
private:
    /**
     * Index Max PQ solution
     *
     * Theta(n log k) time and Theta(n) space
     * as at any point (after adding the first k elements) there are
     * exactly k elements in the index max pq
     */
    static std::vector<int> sol1(const std::vector<int> &nums, int k)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<int> result;
        result.reserve(n - k + 1);

        IndexMaxPQ<int> max_heap(n);
        for (int i = 0; i < k; i++)
            max_heap.insert(i, nums[i]);
        result.push_back(max_heap.max());

        int start{0};
        for (int end = k; end < n; end++)
        {
            max_heap.remove(start++);
            max_heap.insert(end, nums[end]);
            result.push_back(max_heap.max());
        }

        return result;
    }

    /**
     * Index Max PQ solution
     *
     * Theta(n log k) time and Theta(k) space
     * as at any point (after adding the first k elements) there are
     * exactly k elements in the index max pq
     */
    static std::vector<int> sol2(const std::vector<int> &nums, int k)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<int> result;
        result.reserve(n - k + 1);

        IndexMaxPQ<int> max_heap(k);
        for (int i = 0; i < k; i++)
            max_heap.insert(i, nums[i]);
        result.push_back(max_heap.max());

        int start{0};
        for (int end = k; end < n; end++)
        {
            max_heap.remove(start++ % k);
            max_heap.insert(end % k, nums[end]);
            result.push_back(max_heap.max());
        }

        return result;
    }

    /**
     * Monotonically decreasing deque solution
     *
     * Theta(n) time and O(k) space
     */
    static std::vector<int> sol3(const std::vector<int> &nums, int k)
    {
        /**
         * Invariant:
         * For a sliding window, we only store indices of the unique values of running
         * maximum values going from right to left (for duplicate values, we store the
         * index of the right most duplicate as it has a longer lifespan for future
         * windows)
         * Eg:
         *                              0    1    2    3   4   5   6   7   8   9
         *                              ↓    ↓    ↓    ↓   ↓   ↓   ↓   ↓   ↓   ↓
         *       the sliding window: [  4,   2,   9, 100, 20, 19, 13, 14, 13, 13]
         *     the running maximums: [100, 100, 100, 100, 20, 19, 14, 14, 13, 13]
         *            unique values: [100, 20, 19, 14 ,13]
         *
         * We can store the pairs of (index, value) in the deque
         *                   ------------------------------------------
         *   deque: front <-  {3, 100} {4, 20} {5, 19} {7, 14} {9, 13}  <- back
         *                   ------------------------------------------
         *
         * So we can easily find the maximum in a sliding window by getting the
         * left most element in the unique values deque
         */

        // Edge cases
        // (not necessary according to the leetcode problem constraints)
        // if(nums.empty() || k <= 0 || k > n)
        //     return {};

        // Create the result and reserve the space
        int n{static_cast<int>(nums.size())};
        std::vector<int> result;
        result.reserve(n - k + 1);

        // Create the deque that stores the (index, value) pairs
        std::deque<std::pair<int, int>> dq;

        // start and end keep track of the bounds of the sliding window [start, end)
        // start is inclusive and end is not inclusive
        int start{0}, end{0};

        // Process the first sliding window
        // ! Note: we also push the result of this sliding window to the result
        // ! to keep the invariant of the next loop
        while (end < k)
        {
            // Remove all the numbers from the front that are less than or equal to
            // the current number so that we can maintain the invariant
            int num{nums[end]};
            while (!dq.empty() && dq.back().second <= num)
                dq.pop_back();

            // Now either the queue is empty or the right most value is greater
            // than the current number
            // So we can push the number and increment end index
            dq.push_back({end++, num});
        }
        result.push_back(dq.front().second);

        // Invariant for this loop:
        // [start, end) tracks exactly one sliding window at the start of the loop
        // and its maximum has already been processed
        // This is initially maintained as we completely processed the first sliding window
        // before entering this loop
        while (end < n)
        {
            // Remove all the numbers from the front that are less than or equal to
            // the current number so that we can maintain the invariant
            int num{nums[end]};
            while (!dq.empty() && dq.back().second <= num)
                dq.pop_back();

            // Now either the queue is empty or the right most value is greater
            // than the current number
            // So we can push the number and increment end index
            dq.push_back({end++, num});

            // At this point the deque corresponds to a sliding window of length k+1
            // To fix it, we increment start
            start++;

            // Now if the left most value's index is smaller than start, it is out of bounds
            // so we remove it
            if (dq.front().first < start)
                dq.pop_front();

            // At this point the deque corresponds to the new sliding window
            // To keep the invariant, we process the maximum as well
            result.push_back(dq.front().second);
        }

        // Return the result
        return result;
    }

    /**
     * Monotonically decreasing deque solution
     * Very similar to solution 3 except we don't use indices and store the values
     * directly in the deque
     *
     * Theta(n) time and O(k) space
     */
    static std::vector<int> sol4(const std::vector<int> &nums, int k)
    {
        /**
         * Invariant:
         * For a sliding window, we only store values of running maximum values going from right to left
         * Each time a value (in our deque) occurs more than once we store the copies of the duplicate
         * that occur to the right of the value so that when we delete it from the deque,
         * the duplicate which can account for the maximum still stays
         * Eg:
         *                              0    1    2    3   4   5   6   7   8   9
         *                              ↓    ↓    ↓    ↓   ↓   ↓   ↓   ↓   ↓   ↓
         *       the sliding window: [  4, 100,   9, 100, 20, 19, 13, 14, 13, 13]
         *     the running maximums: [100, 100, 100, 100, 20, 19, 14, 14, 13, 13]
         *            unique values: [100, 100, 20, 19, 14, 13, 13]
         *
         * Note that even though 13 occurs thrice, the first 13 is irrelevant as we have a 14 to its right
         *                   ------------------------
         *   deque: front <-  100 100 20 19 14 13 13  <- back
         *                   ------------------------
         *
         * So we can easily find the maximum in a sliding window by getting the
         * left most element in the unique values deque
         */

        // Edge cases
        // (not necessary according to the leetcode problem constraints)
        // if(nums.empty() || k <= 0 || k > n)
        //     return {};

        // Create the result and reserve the space
        int n{static_cast<int>(nums.size())};
        std::vector<int> result;
        result.reserve(n - k + 1);

        // Create the deque that stores the (index, value) pairs
        std::deque<int> dq;

        // start and end keep track of the bounds of the sliding window [start, end)
        // start is inclusive and end is not inclusive
        int start{0}, end{0};

        // Process the first sliding window
        // ! Note: we also push the result of this sliding window to the result
        // ! to keep the invariant of the next loop
        while (end < k)
        {
            // ! Note: we don't remove duplicates from the deque
            // Remove all the numbers from the front that are *less than*
            // the current number so that we can maintain the invariant
            int num{nums[end++]};
            while (!dq.empty() && dq.back() < num)
                dq.pop_back();

            // Now either the queue is empty or the right most value is greater
            // than or equal to the current number
            // So we can push the number and increment end index
            dq.push_back(num);
        }
        result.push_back(dq.front());

        // Invariant for this loop:
        // [start, end) tracks exactly one sliding window at the start of the loop
        // and its maximum has already been processed
        // This is initially maintained as we completely processed the first sliding window
        // before entering this loop
        while (end < n)
        {
            // ! Note: we don't remove duplicates from the deque
            // Remove all the numbers from the front that are less than
            // the current number so that we can maintain the invariant
            int num{nums[end++]};
            while (!dq.empty() && dq.back() < num)
                dq.pop_back();

            // Now either the queue is empty or the right most value is greater
            // than the current number
            // So we can push the number and increment end index
            dq.push_back(num);

            // At this point the deque corresponds to a sliding window of length k+1
            // To fix it, we increment start
            start++;

            // Now if the left most value in the queue is equal to the element
            // that just went out of the sliding window, then we can remove it
            // We use start-1 as we already incremented start and it corresponds
            // to the new sliding window at this point
            if (dq.front() == nums[start - 1])
                dq.pop_front();

            // At this point the deque corresponds to the new sliding window
            // To keep the invariant, we process the maximum as well
            result.push_back(dq.front());
        }

        // Return the result
        return result;
    }

public:
    std::vector<int> maxSlidingWindow(const std::vector<int> &nums, int k) { return sol4(nums, k); }
};