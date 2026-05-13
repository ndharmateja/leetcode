#include <vector>
#include <unordered_map>
#include <algorithm>

/**
 * This enum takes only 1 byte of space as we are using int8_t
 * 0 evaluates to bool value false
 * 1 evaluates to bool value true
 */
enum MemoResult : int8_t
{
    UNCOMPUTED = -1,
    FALSE = 0,
    TRUE = 1
};

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
        long long total_sum{0};
        for (auto num : nums)
            total_sum += num;
        if (total_sum & 1)
            return false;
        std::unordered_map<uint64_t, bool> memo;
        return sol1(nums, 0, nums.size(), 0, total_sum, memo);
    }

    /**
     * Bottom up DP solution
     *
     * O(n*target) time and Theta(n*target) space
     * where n = number of elements in the list
     * and target = sum(nums)/2
     */
    static bool sol2(const std::vector<int> &nums)
    {
        /**
         * * Explanation
         * target is the sum(nums)/2. If the total sum is odd then we can't partition the list.
         * If it is even then if we can find out if there is a subset that sums to target
         * then the remaining numbers also sum to target.
         * * DP solution
         * dp[i][k]: true    if nums[i:] has a subset of elements that sum to k
         *         : false   otherwise
         * dp array's dimensions will be (n+1)x(target+1)
         * where n is the #elements in the list
         * * Base case
         * dp[i][0] = true
         * as we can only form 0 from an any set of numbers
         * * Recurrence relation
         * Similar to 0/1 Knapsack
         * nums[i] is either part of the subset that sums to k or not
         * if it is not part of the subset, then nums[i+1:] should have a subset summing k
         * if it is part of the subset, then nums[i+1:] should have a subset summing k-nums[i]
         * dp[i][k] = dp[i+1][k] || dp[i+1][k-nums[i]]  (if k - nums[i] >= 0)
         * * Order of filling
         * For each i going from n-1 to 0, we can fill each row in any order
         * as we only need values from 'i+1'th row
         * But it is better to fill from the right to left to immediately know
         * if target can be formed so that we can immediatly exit
         * * Final answer
         * any{dp[i][target] for i in [0, n-1]}
         * * Running time
         * #subproblems = (n+1)*(target+1)
         * work per subproblem = Theta(1)
         * postprocessing = Theta(1)
         * total time = Theta(n*target)
         */

        // Compute the total sum and exit if it is odd
        int n{static_cast<int>(nums.size())};
        long long total_sum{0};
        for (auto num : nums)
            total_sum += num;
        if (total_sum & 1)
            return false;

        // The target is half of the total sum
        int target = total_sum >> 1;
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

        // Base case
        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        // Fill the table from the last row to the first
        for (int i = n - 1; i >= 0; i--)
        {
            // ! Extra optimization: If a number is greater than the target
            // ! we can immediately return false as the remaining numbers can't sum
            // ! up to target as every number is positive
            int num = nums[i];
            if (target < num)
                return false;

            // Compute dp[i][target] first (by going right to left) first
            // so that we can immediately exit if target can be formed from a subset
            // in nums[i:]
            // ! dp[i][target] = dp[i + 1][target] ||
            // !                 (target < num
            // !                     ? false
            // !                     : dp[i + 1][target - num]);
            // ! Instead of above code, we can use the below code
            // ! we don't need to see if dp[i+1][target] is true as we'd already return
            // ! if that were true
            // ! We also don't need to check the target < num as we have an if condition above
            // ! checking if (target < num)
            dp[i][target] = dp[i + 1][target - num];
            if (dp[i][target])
                return true;

            // If i=0 and we reach here we hadn't found any i for which dp[i][target]
            // is true. So we don't need to compute the remaning values in the 0th row.
            if (i == 0)
                return false;

            // Fill the row from right to left
            for (int k = target - 1; k >= 1; k--)
                dp[i][k] = dp[i + 1][k] ||
                           (k < num ? false : dp[i + 1][k - num]);
        }

        // We would never reach here
        // as we have an exit condition check when i = 0
        return false;
    }

    /**
     * Space optimized version of solution2
     * Read that solution in detail first.
     *
     * O(n*target) time and Theta(target) space
     * where n = number of elements in the list
     * and target = sum(nums)/2
     */
    static bool sol3(const std::vector<int> &nums)
    {
        /**
         * Explanation:
         * We only need the (i+1)th row for
         */

        // Compute the total sum and exit if it is odd
        int n{static_cast<int>(nums.size())};
        long long total_sum{0};
        for (auto num : nums)
            total_sum += num;
        if (total_sum & 1)
            return false;

        // The target is half of the total sum
        int target = total_sum >> 1;
        std::vector<bool> dp(target + 1, false);

        // Base case
        dp[0] = true;

        // Fill the table from the last row to the first
        for (int i = n - 1; i >= 0; i--)
        {
            // ! Extra optimization: If a number is greater than the target
            // ! we can immediately return false as the remaining numbers can't sum
            // ! up to target as every number is positive
            int num = nums[i];
            if (target < num)
                return false;

            // Compute dp[i][target] first (by going right to left) first
            // so that we can immediately exit if target can be formed from a subset
            // in nums[i:]
            dp[target] = dp[target - num];
            if (dp[target])
                return true;

            // If i=0 and we reach here we hadn't found any i for which dp[i][target]
            // is true. So we don't need to compute the remaning values in the 0th row.
            if (i == 0)
                return false;

            // ! We would have to fill this table from right to left
            // ! since we are using values from the 'i+1'th row with index 'k-num'
            // ! So we should not update dp[k-num] first because the 'i+1'th row's
            // ! value would be overwritten

            // ! for (int k = target - 1; k >= 1; k--)
            // !     dp[k] = dp[k] ||
            // !             (k < num ? false : dp[k - num]);
            // ! What this above loop is doing is that
            // ! when k >= num, we are doing dp[k] = dp[k] || dp[k-num]
            // ! when k < num,  we are doing dp[k] = dp[k] which is not changing dp[k]'s val
            // ! So we can change the condition from k >= 1 to k >= num
            // ! and the code to 'dp[k] = dp[k] || dp[k - num]'
            // ! which means that we are updating dp[k] to true if dp[k-num] is true
            // ! otherwise the value in dp[k] is not changed, this is the same as code below
            for (int k = target - 1; k >= num; k--)
                if (dp[k - num])
                    dp[k] = true;
        }

        // We would never reach here
        // as we have an exit condition check when i = 0
        return false;
    }

    static bool sol4(const std::vector<int> &nums,
                     const int i, const int n, const int target,
                     std::vector<std::vector<MemoResult>> &memo)
    {
        if (i == n)
            return target == 0;
        if (target < 0)
            return false;
        MemoResult &answer = memo[i][target];
        if (answer != MemoResult::UNCOMPUTED)
            return answer;
        answer = (sol4(nums, i + 1, n, target, memo) ||
                  sol4(nums, i + 1, n, target - nums[i], memo))
                     ? MemoResult::TRUE
                     : MemoResult::FALSE;
        return answer;
    }

    /**
     * Top down DP version of solution 2
     * Read that first in detail.
     */
    static bool sol4(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        long long total_sum{0};
        for (auto num : nums)
            total_sum += num;
        if (total_sum & 1)
            return false;
        int target = total_sum >> 1;
        std::vector<std::vector<MemoResult>> memo(n + 1, std::vector<MemoResult>(target + 1, MemoResult::UNCOMPUTED));
        return sol4(nums, 0, n, target, memo);
    }

    /**
     * TODO: Bottom up DP solution in increasing order of i
     */
    static bool sol5(const std::vector<int> &nums) { return false; }

public:
    bool canPartition(const std::vector<int> &nums) { return sol3(nums); }
};