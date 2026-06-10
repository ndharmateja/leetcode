#include <vector>

/**
 * Mixture of solutions 1 and 2
 */
class Solution
{
private:
    static void backtrack(const std::vector<int> &nums, const int target,
                          const size_t min_index, const size_t nums_len,
                          std::vector<std::vector<int>> &result, std::vector<int> &buf)
    {
        if (!target)
        {
            result.push_back(buf);
            return;
        }

        if (target < 0)
            return;

        for (size_t i = min_index; i < nums_len; i++)
        {
            int candidate = nums[i];
            buf.push_back(candidate);
            backtrack(nums, target - candidate, i, nums_len, result, buf);
            buf.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> buf;
        backtrack(nums, target, 0, nums.size(), result, buf);
        return result;
    }

public:
    std::vector<std::vector<int>>
    combinationSum(const std::vector<int> &nums, int target) { return sol(nums, target); }
};