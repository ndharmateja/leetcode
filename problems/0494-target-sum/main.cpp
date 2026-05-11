#include <vector>
#include <unordered_map>
#include <utility>
#include <cstdint>

class Solution
{
private:
    static int sol1(const std::vector<int> &nums,
                    int i, int sum,
                    std::unordered_map<uint64_t, int> &memo)
    {
        // Base case
        // ! We are not storing the base cases in the memo to store space as there
        // ! could be multiple base cases
        // We can do that by returning a sum of values
        // We need to add both cases as sum and nums.front() can both be 0
        // in which case the #ways would be 2
        if (i == 0)
            return (sum == nums.front() ? 1 : 0) + (sum == -nums.front() ? 1 : 0);

        // If the memo contains the answer already, we can return it
        // We are forming a 64bit uint64_t key by packing the i and sum next to each other
        uint64_t key = (static_cast<uint64_t>(i) << 32) | (static_cast<unsigned>(sum));
        auto [it, inserted] = memo.try_emplace(key, -1);
        if (!inserted)
            return it->second;

        // Otherwise we insert after recursively computing the solution and return it
        it->second = sol1(nums, i - 1, sum + nums[i], memo) + sol1(nums, i - 1, sum - nums[i], memo);
        return it->second;
    }

    /**
     * Top down DP approach
     */
    static int sol1(const std::vector<int> &nums, int sum)
    {
        /**
         * * DP solution
         * dp[i, sum]: #ways we can form 'sum' using indices [0, i] of nums
         * * Base case
         * dp[0, sum] = 1  if sum == nums[0] or sum == -nums[0]
         *            = 0  otherwise
         * * Recurrence relation
         * dp[i, sum] = dp[i-1, sum+1] + dp[i-1, sum-1]
         * * Final answer: dp[n-1, target]
         */
        // Base case
        // We can do that by returning a sum of values
        // We need to add both cases as sum and nums.front() can both be 0
        // in which case the #ways would be 2
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return (sum == nums.front() ? 1 : 0) + (sum == -nums.front() ? 1 : 0);

        // General case
        std::unordered_map<uint64_t, int> memo;
        memo.reserve(n - 1);
        return sol1(nums, n - 1, sum, memo);
    }

    static int sol2(const std::vector<int> &nums,
                    int i, int target, int total_prefix_sum_till_i, int total_sum,
                    std::vector<std::vector<int>> &memo)
    {
        // Base case
        // ! We are not storing the base cases in the memo to store space as there
        // ! could be multiple base cases
        // We can do that by returning a sum of values
        // We need to add both cases as sum and nums.front() can both be 0
        // in which case the #ways would be 2
        if (i == 0)
            return (target == nums.front() ? 1 : 0) + (target == -nums.front() ? 1 : 0);

        // Edge case to prevent index out of bounds for the second index
        // Eg: nums=[1, 1, 1, 1, 1] and target=-5
        // In the first recursive call we would check for i = 3 and target = -6 as well
        // which can make target + total_sum = -1 thereby giving an invalid index
        // ! We can do extra optimization as the target cannot be greater than prefix_sum_till_i
        // ! or smaller than -prefix_sum_till_i (eliminates more cases than checking against total_sum)
        // ! We still need the total_sum for the offset to keep the second index non-negative
        if (target < -total_prefix_sum_till_i || target > total_prefix_sum_till_i)
            return 0;

        // If the memo contains the answer already, we can return it
        // We are forming a 64bit uint64_t key by packing the i and sum next to each other
        int &result = memo[i][target + total_sum];
        if (result != -1)
            return result;

        // Otherwise we insert after recursively computing the solution and return it
        result = sol2(nums, i - 1, target + nums[i], total_prefix_sum_till_i - nums[i], total_sum, memo) +
                 sol2(nums, i - 1, target - nums[i], total_prefix_sum_till_i - nums[i], total_sum, memo);
        return result;
    }

    /**
     * Same as solution 1 except we are using a 2D vector of ints as the memo
     * instead of the unordered map
     * since target can be -ve, we add it with offset of total_sum to make it >= 0
     * so that we can use that as the second index
     */
    static int sol2(const std::vector<int> &nums, int target)
    {
        // Base case
        // We can do that by returning a sum of values
        // We need to add both cases as sum and nums.front() can both be 0
        // in which case the #ways would be 2
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return (target == nums.front() ? 1 : 0) + (target == -nums.front() ? 1 : 0);

        // Edge case
        // If target is greater than total_sum or smaller than -total_sum, we can return 0
        int total_sum{0};
        for (int num : nums)
            total_sum += num;
        if (target < -total_sum || target > total_sum)
            return 0;

        // General case
        std::vector<std::vector<int>> memo(n, std::vector<int>(2 * total_sum + 1, -1));
        return sol2(nums, n - 1, target, total_sum, total_sum, memo);
    }

public:
    int findTargetSumWays(const std::vector<int> &nums, int target) { return sol2(nums, target); }
};