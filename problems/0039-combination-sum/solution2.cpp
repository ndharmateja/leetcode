#include <vector>

/**
 * Mixture of solutions 1 and 2:
 * static void backtrack(const std::vector<int> &candidates, int target,
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
 */

class Solution
{
private:
    // Appends all the vectors (to the result) that sum upto target using nums[min_index:]
    static void backtrack(std::vector<std::vector<int>> &result,
                          const std::vector<int> &nums, std::vector<int> &buf, const int buf_sum,
                          const int target, const size_t min_index, const size_t nums_len)
    {
        if (buf_sum > target)
            return;

        // Base cases
        // ! Redundant: Since our for loop ends at nums_len-1
        // 1. If min_index itself becomes the size of nums, then nums[min_index:] is
        //    an empty array, so we can exit
        // if (min_index == nums_len)
        // return;

        // 2. If target is 0, we can form 0 using an empty list using nums[min_index:]
        //    and since all numbers are positive we don't need to explore this branch
        //    further as we would be only going along negative numbers as targets
        if (buf_sum == target)
        {
            result.push_back(buf);
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
            buf.push_back(curr_num);
            backtrack(result, nums, buf, buf_sum + curr_num, target, i, nums_len);
            buf.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> buf;
        backtrack(result, nums, buf, 0, target, 0, nums.size());
        return result;
    }

public:
    std::vector<std::vector<int>>
    combinationSum(const std::vector<int> &candidates, int target) { return sol(candidates, target); }
};