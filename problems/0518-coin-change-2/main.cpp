#include <vector>

class Solution
{
private:
    static void backtrack(const std::vector<int> &candidates, int target,
                          int candidate_start_index, int num_candidates,
                          std::vector<std::vector<int>> &result, std::vector<int> &buffer)
    {
        if (!target)
        {
            result.push_back(buffer);
            return;
        }

        if (target < 0)
            return;

        for (int i = candidate_start_index; i < num_candidates; i++)
        {
            int candidate = candidates[i];
            buffer.push_back(candidate);
            backtrack(candidates, target - candidate, i, num_candidates, result, buffer);
            buffer.pop_back();
        }
    }

    static std::vector<std::vector<int>>
    sol1(const std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> buffer;
        int num_candidates = static_cast<int>(candidates.size());
        backtrack(candidates, target, 0, num_candidates, result, buffer);
        return result;
    }

    static int dfs(const std::vector<int> &nums, int target, int i, int buffer_sum, std::vector<std::vector<int>> &memo)
    {

        // If the buffer_sum crosses the target, then there is no point continuing
        // as all the numbers are positive
        if (buffer_sum > target)
            return 0;

        // If we reach the end, we don't need to do anything
        // so we can simply return
        if (i == nums.size())
            return 0;

        // If targer sum is found, we can add this sequence to our result and exit
        int &result = memo[i][buffer_sum];
        if (result != -1)
            return result;

        if (buffer_sum == target)
            return (result = 1);

        // Two options pick the current one or don't pick the current one
        // 1. If we pick the current one, we add that to the current sum
        // and the current list to track the sequence and then
        // we call the dfs starting from *the same element* again
        // as each element can be picked multiple times
        // That is why we call dfs again from 'i' instead of 'i+1'
        result = 0;
        result += dfs(nums, target, i, buffer_sum + nums[i], memo);

        // 2. If we don't pick the current element, we call dfs starting from the
        // next element
        result += dfs(nums, target, i + 1, buffer_sum, memo);
        return result;
    }

    int sol2(int target, const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> memo(n, std::vector<int>(target + 1, -1));
        return dfs(nums, target, 0, 0, memo);
    }

public:
    int change(int amount, const std::vector<int> &coins) { return sol2(amount, coins); }
};