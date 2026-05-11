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
        // We can do that by returning a sum of  boolean values as a true evaluates to 1
        // and a false evaluates to 0
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
        int n{static_cast<int>(nums.size())};
        if (n == 0)
            return (sum == nums.front() ? 1 : 0) + (sum == -nums.front() ? 1 : 0);

        // General case
        std::unordered_map<uint64_t, int> memo;
        memo.reserve(n - 1);
        return sol1(nums, n - 1, sum, memo);
    }

public:
    int findTargetSumWays(const std::vector<int> &nums, int target) { return sol1(nums, target); }
};