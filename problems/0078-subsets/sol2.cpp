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

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<int> buffer;
        std::vector<std::vector<int>> result;
        result.reserve(1 << n);
        backtrack(nums, 0, n, result, buffer);
        return result;
    };

public:
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums) { return sol(nums); };
};