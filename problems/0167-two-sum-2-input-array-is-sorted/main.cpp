#include <vector>

class Solution
{
private:
    /**
     * Two pointer solution
     * Theta(n) time and Theta(1) space in worst case
     *
     * State machine:
     * States: the pairs [lo, hi] for the array
     * Initial state: [lo=0, hi=n-1]
     * Transitions:
     * 1. if array[lo] + array[hi] > target then [lo, hi-1]
     * 2. if array[lo] + array[hi] < target then [lo+1, hi]
     * Final state: [lo, hi] such that array[lo] + array[hi] = target
     * Predicate: Solution always exists in the [lo, hi] range
     * Proof:
     * Base case: If the solution exists, then it is in the whole array
     * so it is in the [0, n-1] range
     * Preserved predicate: For every transition r -> s, if the predicate is true for r, then it is true for s
     * for the first kind of transition, if solution exists in [lo, hi] and
     * array[lo] + array[hi] > target then array[i] + array[hi] > target
     * for all i in [lo, hi-1] as they are sorted in non-decreasing order
     * so array[hi] can't add up with another number in the [lo, hi-1] range
     * to add up to target. so we can eliminate hi index => predicate is
     * preserved for this transition.
     * Similar argument can be made for the second transition too.
     * Hence the predicate is a preserved predicate.
     * Since the predicate is true for the initial state and is a preserved
     * predicate, it is an invariant.
     */
    static std::vector<int> solution1(const std::vector<int> &nums, int target)
    {
        int lo{0}, hi{static_cast<int>(nums.size()) - 1};
        while (lo < hi)
        {
            // If the sum of values at lo and hi is smaller than the target
            // then we increment the left pointer
            int sum = nums[lo] + nums[hi];
            if (sum < target)
                lo++;

            // If the sum of values at lo and hi is greater than the target
            // then we decrement the right pointer
            else if (sum > target)
                hi--;

            // If the sum of values at lo and hi is equal to the target
            // we found the solution
            // Answer should be returned as 1-indexed
            else
                return {lo + 1, hi + 1};
        }

        // Since there always exists a solution, we would never reach here
        return {-1, -1};
    }

    /**
     * Binary search of key in nums. Returns the index of the rightmost occurrence
     * of key in nums. If the key doesn't exist, it returns -1.
     * Uses candidate variable pattern.
     */
    static int binary_search(const std::vector<int> &nums, int key)
    {
        int lo{0}, hi{static_cast<int>(nums.size()) - 1}, mid;
        int answer = -1;
        while (lo <= hi)
        {
            // If the key is smaller than the middle value, we look for the key
            // in the left half
            mid = lo + (hi - lo) / 2;
            if (key < nums[mid])
                hi = mid - 1;

            // If the key is smaller than the middle value, we look for the key
            // in the left half
            else if (key > nums[mid])
                lo = mid + 1;

            // If the key is equal to the middle value, it means we found a potential
            // solution but the right half might have a better solution as we are looking
            // for the right most value
            else
            {
                answer = mid;
                lo = mid + 1;
            }
        }

        return answer;
    }

    /**
     * Binary search solution
     * Theta(n log n) time and Theta(1) space in worst case
     */
    static std::vector<int> solution2(const std::vector<int> &nums, int target)
    {
        // Init variables
        int n{static_cast<int>(nums.size())};

        // For each number do binary search and find its complement
        for (int i = 0; i < n; i++)
        {
            // Find the right most occurrence of complement in nums
            // using binary search
            int complement = target - nums[i];
            int complement_index = binary_search(nums, complement);

            // If the complement doesn't exist, we can go to the next number
            if (complement_index == -1)
                continue;

            // If i == complement_index, it means that the complement is equal to the nums[i]
            // itself. it means that the complement = nums[i] = target/2
            // and if binary search (that returns the right most occurrence)
            // of the complement is the same as 'i' itself, it means that
            // we found the index of the exact same element. Because the binary search
            // is looking for the rightmost occurrence, if there were a duplicate of
            // nums[i], its index would be different from 'i' as i is going from
            // left to right.
            if (i == complement_index)
                continue;

            // At this point we have a valid answer
            // We add 1s as the answer is needed in 1-indexed format
            return {i + 1, complement_index + 1};
        }

        // We would never reach here as there is a valid answer
        return {-1, -1};
    }

public:
    std::vector<int> twoSum(const std::vector<int> &nums, int target) { return solution1(nums, target); }
};