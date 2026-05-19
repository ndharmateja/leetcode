#include <vector>

class Solution
{
private:
    static constexpr int factorial[] = {1, 1, 2, 6, 24, 120, 720};

    static void backtrack(const std::vector<int> &nums, std::vector<bool> &visited,
                          int idx, int n,
                          std::vector<std::vector<int>> &result, std::vector<int> &buffer)
    {
        if (idx == n)
        {
            result.push_back(buffer);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;

            buffer.push_back(nums[i]);
            visited[i] = true;
            backtrack(nums, visited, idx + 1, n, result, buffer);
            visited[i] = false;
            buffer.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol1(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        result.reserve(factorial[n]);
        std::vector<bool> visited(n, false);
        std::vector<int> buffer;
        backtrack(nums, visited, 0, n, result, buffer);
        return result;
    }

public:
    std::vector<std::vector<int>> permute(const std::vector<int> &nums) { return sol1(nums); }
};