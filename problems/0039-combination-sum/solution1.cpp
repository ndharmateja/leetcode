#include <vector>

class Solution
{
private:
    // Appends all the vectors (to the result) that sum upto target using nums[min_index:]
    static void backtrack(std::vector<std::vector<int>> &result, const std::vector<int> &nums,
                          const int target, const size_t min_index, const size_t nums_len)
    {
        // If target becomes less than 0, we can ignore this branch
        if (target < 0)
            return;

        // Base cases
        // 1. If min_index itself becomes the size of nums, then nums[min_index:] is
        //    an empty array, so we can exit
        if (min_index == nums_len)
            return;

        // 2. If target is 0, we can form 0 using an empty list using nums[min_index:]
        //    and since all numbers are positive we don't need to explore this branch
        //    further as we would be only going along negative numbers as targets
        if (target == 0)
        {
            result.push_back({});
            return;
        }

        // Eg: Before the function call, let's say the values are
        // nums: [2, 3, 9], min_index = 1, target = 9, result = [<some lists>]
        //
        // We first call
        // backtrack(result, nums, target=9-3=6, min_index=1)
        // We still use min_index=1 as even though we used nums[min_index=1] = 3,
        // we can still use it again
        // So the recursive call essentially adds all the lists that add up to 6
        // using nums[1:] = [3, 9]
        // So result will be [<some lists>, [3, 3]]
        // So we append 3 to all the newly added lists to the result as the target
        // in this function is 9.
        // So after this call we make result as [<some lists>, [3, 3, 3]]
        //
        // We next call
        // backtrack(result, nums, target=9-9=0, min_index=2)
        // So the recursive call essentially adds all the lists that add up to 0
        // using nums[2:] = [9]
        // So result will be [<some lists>, [3, 3, 3], []]
        // So we append 3 to all the newly added lists to the result as the target
        // in this function is 9.
        // So after this call we make result as [<some lists>, [3, 3, 3], [9]]
        for (size_t i = min_index; i < nums_len; ++i)
        {
            int curr_num{nums[i]};
            size_t result_size_before{result.size()};
            backtrack(result, nums, target - curr_num, i, nums_len);
            for (size_t j = result_size_before; j < result.size(); ++j)
                result[j].push_back(curr_num);
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;
        backtrack(result, nums, target, 0, nums.size());
        return result;
    }

public:
    std::vector<std::vector<int>>
    combinationSum(const std::vector<int> &candidates, int target) { return sol(candidates, target); }
};