#include <vector>

class Solution
{
private:
    static void backtrack(const std::vector<int> &nums, const int idx, const int n,
                          std::vector<std::vector<int>> &result, std::vector<int> &buffer)
    {
        if (idx == n)
        {
            result.push_back(buffer);
            return;
        }

        backtrack(nums, idx + 1, n, result, buffer);
        buffer.push_back(nums[idx]);
        backtrack(nums, idx + 1, n, result, buffer);
        buffer.pop_back();
    };

    static std::vector<std::vector<int>> sol1(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<int> buffer;
        std::vector<std::vector<int>> result;
        result.reserve(1 << n);
        backtrack(nums, 0, n, result, buffer);
        return result;
    };

    static void backtrack2(const std::vector<int> &nums, const int idx, const int n,
                           std::vector<std::vector<int>> &result)
    {
        if (idx == n)
        {
            result.push_back(std::vector<int>());
            return;
        }

        backtrack2(nums, idx + 1, n, result);

        // ! We can't do a for each loop as we are also modifying the result in the loop
        int result_size{static_cast<int>(result.size())};
        for (int i = 0; i < result_size; i++)
        {
            result.push_back(result[i]);
            result.back().push_back(nums[idx]);
        }
    };

    static std::vector<std::vector<int>> sol2(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        result.reserve(1 << n);
        backtrack2(nums, 0, n, result);
        return result;
    };

    static std::vector<std::vector<int>> sol3(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        result.reserve(1 << n);
        result.push_back({});
        int result_size{1};
        for (const int num : nums)
        {
            for (int i = 0; i < result_size; i++)
            {
                result.push_back(result[i]);
                result.back().push_back(num);
            }
            result_size <<= 1;
        }
        return result;
    };

public:
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums) { return sol3(nums); };
};