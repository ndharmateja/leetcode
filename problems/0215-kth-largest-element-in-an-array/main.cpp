#include <vector>
#include <algorithm>
#include <random>
#include <queue>

class Solution
{
private:
    static void shuffle_vector(std::vector<int> &nums)
    {
        // obtain a random seed from the generator
        std::random_device rd;
        std::mt19937 g(rd());

        // perform the shuffle
        std::shuffle(nums.begin(), nums.end(), g);
    }
    /**
     * Iterative quick select
     *
     * O(n) time on average and O(1) space
     */
    static int solution1(std::vector<int> &nums, int k)
    {
        // Init variables
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1};
        std::pair<int, int> pivot_range;

        // Given: 1 <= k <= n
        // If we need the kth largest, it is equivalent to finding
        // the element at index 'n - k' in the sorted order
        // So we essentially need to select the (n-k)th smallest element (0-index)
        // means that 0 <= k < n now
        k = n - k;

        // Shuffle the given array for good probabilistic performance
        // and avoid pathological cases
        shuffle_vector(nums);

        // Run iterative quick select
        while (lo <= hi)
        {
            // We do a 3-way parition to avoid the pathological case of
            // a lot of duplicates
            pivot_range = three_way_partition(nums, lo, hi);

            // If the given k in the given range, we found it
            if (pivot_range.first <= k && k <= pivot_range.second)
                return nums[k];

            // If k is smaller than the pivot range, then we look for it in the left half
            if (k < pivot_range.first)
                hi = pivot_range.first - 1;

            // Else, k is *greater* than the pivot range as the first <= k <= second
            // has already been handled
            else
                lo = pivot_range.second + 1;
        }

        // We never reach here given that our transformed 'k' is in the range [0, n)
        return -1;
    }

    static std::pair<int, int> three_way_partition(std::vector<int> &nums, int lo, int hi)
    {
        // Pivot is the left most element in the range
        const int pivot = nums[lo];

        // Invariant
        //            j         i                      k
        //            ↓         ↓                      ↓
        // [   <p   ][   =p   ][          ....          ][   >p   ]
        // variables: j, i, k
        // j: keeps track of the first element in the =p range
        // i: keeps track of the first element in the to be seen yet range
        // k: keeps track of the last element in the to be seen yet range
        // so, the number of elements to be seen yet become 0 (partition being done)
        // when i just crosses k <=> i = k + 1
        // Initially, only the first value is p. So the j starts at lo because no
        // elements in the <p range. i starts at lo + 1 because of the first element being
        // the pivot (=p). and k at hi as no elements >p in the range.
        int j{lo}, i{lo + 1}, k{hi};
        while (i != k + 1)
        {
            // If the current number == pivot, it means that it is already in its place
            // so we simply increment i
            const int curr_num = nums[i];
            if (curr_num == pivot)
                i++;

            // If the current number < pivot, we swap it with the left most element
            // in the =p range so that it is right next to the <p range.
            // We increment i and j accordingly
            else if (curr_num < pivot)
                std::swap(nums[i++], nums[j++]);

            // Else, the current number > pivot, we swap it with the right most element
            // in the >p range so that it is first element in the >p range.
            // We decrement k accordingly. i doesn't change as a new element to be seen yet
            // has come from the >p range at index i.
            else
                std::swap(nums[i], nums[k--]);
        }

        // The range of =p is [j, i - 1]
        return {j, i - 1};
    }

    /**
     * Sorting solution
     *
     * Theta(n log n) time and Theta(logn) space (potentially for the sort function)
     */
    static int solution2(std::vector<int> &nums, int k)
    {
        // Given: 1 <= k <= n
        // If we need the kth largest, it is equivalent to finding
        // the element at index 'n - k' in the sorted order
        // So we essentially need to select the (n-k)th smallest element (0-index)
        // means that 0 <= k < n now
        k = nums.size() - k;
        std::sort(nums.begin(), nums.end());
        return nums[k];
    }

    /**
     * Min heap solution. only store the top-k elements at any point
     * Theta(n log k) time and Theta(k) space
     *
     * This heap solution works better for streams and when we don't want
     * the input array to be mutated. Both solution 1 (shuffle) and solution 2 (sort)
     * mutate the given input. This also has a worst case guarantee of Theta(n log k)
     * unlike the quick select which has a worst case running time of Theta(n^2) but
     * is faster in practice.
     */
    static int solution3(std::vector<int> &nums, int k)
    {
        // We use a min heap (hence std::greater<>)
        // At any point, the heap has k largest elements (except until we reach the size of k)
        // of the nums seen so far
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        for (const auto &num : nums)
        {
            pq.push(num);
            if (pq.size() > k)
                pq.pop();
        }

        // The kth largest in the whole group is the min value in the heap
        // at this point as the heap has the k largest elements from the whole group
        return pq.top();
    }

public:
    int findKthLargest(std::vector<int> &nums, int k) { return solution1(nums, k); }
};