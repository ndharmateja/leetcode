#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
private:
    /**
     * Recursively function to compute if nums[i:] can be partitioned into two subsets
     * whose difference is @param difference
     * @param total_sum is the sum of values in the sublist nums[i:]
     *
     * We can keep the @param difference positive to reduce the #unique (i, difference) pairs
     */
    static bool sol1(const std::vector<int> &nums,
                     const int i, const int n, const int difference, const int total_sum,
                     std::unordered_map<uint64_t, bool> &memo)
    {
        // Base case
        if (i == n)
            return difference == 0;

        // If the difference gets larger than the total sum, we can't create that
        if (difference > total_sum)
            return false;

        // If the memo contains the answer already, we can return it
        // We are forming a 64bit uint64_t key by packing the i and sum next to each other
        uint64_t key = (static_cast<uint64_t>(i) << 32) | (static_cast<unsigned>(difference));
        auto [it, inserted] = memo.try_emplace(key, -1);
        if (!inserted)
            return it->second;

        // Recursively compute the answer (short circuting)
        it->second = (sol1(nums, i + 1, n, std::abs(difference - nums[i]), total_sum - nums[i], memo) ||
                      sol1(nums, i + 1, n, std::abs(difference + nums[i]), total_sum - nums[i], memo));
        return it->second;
    }

    /**
     * Naive top down DP solution
     */
    static bool sol1(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())}, total_sum{0};
        for (auto num : nums)
            total_sum += num;
        std::unordered_map<uint64_t, bool> memo;
        return sol1(nums, 0, nums.size(), 0, total_sum, memo);
    }

public:
    bool canPartition(const std::vector<int> &nums) { return sol1(nums); }
};