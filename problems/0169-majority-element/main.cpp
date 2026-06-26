#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
private:
    /**
     * Hashmap based solution
     * Theta(n) time and Theta(n) space
     */
    static int sol1(const std::vector<int> &nums)
    {
        // The number of distinct elements is atmost n/2 + 1
        // as more than half of the elements are the same majority element
        int half_n{static_cast<int>(nums.size()) / 2};
        std::unordered_map<int, int> counts;
        counts.reserve(half_n + 1);

        // Compute the counts
        for (int num : nums)
        {
            auto [it, inserted] = counts.try_emplace(num, 0);
            it->second++;
        }

        // Return the number with count > n/2
        for (auto &[num, count] : counts)
            if (count > half_n)
                return num;

        // We will never reach here as we are guaranteed the presence of
        // a majority element
        return -1;
    }

    /**
     * Theta(n) time and Theta(1) space
     */
    static int sol2(const std::vector<int> &nums)
    {
        int result, count{0};
        for (int num : nums)
            if (count)
                count += (num == result ? 1 : -1);
            else
            {
                result = num;
                count = 1;
            }

        // Result is the answer as we are guaranteed a majority
        return result;
    }

    // Using a sentinel value outside the [-10^9, 10^9] range to indicate
    // no majority. This could have been implemented in multiple ways even if
    // the range is the range of int (return a pair<bool, int> or optional<int> etc)
    static inline const int NO_MAJORITY = -1'000'000'001;

    /**
     * Finds the majority element in the [lo, hi] range if it exists
     */
    static int sol3(const std::vector<int> &nums, int lo, int hi)
    {
        // Base case
        if (lo == hi)
            return nums[lo];

        // Recursively find the majority elements in both halfs
        int mid = lo + (hi - lo) / 2;
        int left_majority = sol3(nums, lo, mid);
        int right_majority = sol3(nums, mid + 1, hi);

        // If both majorities are same it means that that is the majority element
        if (left_majority == right_majority)
            return left_majority;

        // If either of the left/right majority element (if exists) is the total majority
        // element in the range, we return it
        int half_n{(hi - lo + 1) / 2};
        if (left_majority != NO_MAJORITY &&
            std::count(nums.begin() + lo, nums.begin() + hi + 1, left_majority) > half_n)
            return left_majority;
        if (right_majority != NO_MAJORITY &&
            std::count(nums.begin() + lo, nums.begin() + hi + 1, right_majority) > half_n)
            return right_majority;

        // If we reach here, either one/both halves didn't have a majority element
        // or the majority element candidates from each half wasn't a majority element
        // in the whole range
        return NO_MAJORITY;
    }

    /**
     * Divide and conquer solution
     * Theta(n log n) time and Theta(log n) space
     * Recurrence relation is T(n) = 2T(n/2) + Theta(n) in the worst case
     */
    static int sol3(const std::vector<int> &nums) { return sol3(nums, 0, nums.size() - 1); }

public:
    int majorityElement(const std::vector<int> &nums) { return sol2(nums); }
};