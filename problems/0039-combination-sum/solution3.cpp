#include <vector>

class Solution
{
private:
    static void backtrack(const std::vector<int> &nums, int target, int i, int buffer_sum,
                          std::vector<int> &buffer, std::vector<std::vector<int>> &result)
    {
        // If the buffer_sum crosses the target, then there is no point continuing
        // as all the numbers are positive
        if (buffer_sum > target)
            return;

        // If targer sum is found, we can add this sequence to our result and exit
        if (buffer_sum == target)
        {
            result.push_back(buffer);
            return;
        }

        // If we reach the end, we don't need to do anything
        // so we can simply return
        if (i == nums.size())
            return;

        // Two options pick the current one or don't pick the current one
        // 1. If we pick the current one, we add that to the current sum
        // and the current list to track the sequence and then
        // we call the backtrack starting from *the same element* again
        // as each element can be picked multiple times
        // That is why we call backtrack again from 'i' instead of 'i+1'
        buffer.push_back(nums[i]);
        backtrack(nums, target, i, buffer_sum + nums[i], buffer, result);
        buffer.pop_back();

        // 2. If we don't pick the current element, we call backtrack starting from the
        // next element
        backtrack(nums, target, i + 1, buffer_sum, buffer, result);
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> buffer;
        backtrack(nums, target, 0, 0, buffer, result);
        return result;
    }

public:
    std::vector<std::vector<int>>
    combinationSum(const std::vector<int> &candidates, int target) { return sol(candidates, target); }
};