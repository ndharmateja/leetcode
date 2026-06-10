#include <vector>
#include <map>

class Solution
{
private:
    static void backtrack(std::vector<std::vector<int>> &result, std::vector<int> &buf,
                          std::vector<std::pair<int, int>> &nums_counts,
                          const int min_index, const int target)
    {
        if (!target)
        {
            result.push_back(buf);
            return;
        }

        if (target < 0)
            return;

        for (size_t i = min_index; i < nums_counts.size(); ++i)
        {
            auto &[num, count] = nums_counts[i];
            if (!count)
                continue;

            // ! Search space pruning: if the smallest number (nums_counts[i:].first = num)
            // ! is itself larger than targetj, then we cannot form target
            // ! So we can completely skip remaining numbers
            if (target < num)
                break;

            buf.push_back(num);
            count--;
            backtrack(result, buf, nums_counts, i, target - num);
            count++;
            buf.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums, int target)
    {
        std::map<int, int> counts;
        for (const int num : nums)
        {
            auto [it, inserted] = counts.try_emplace(num, 1);
            if (!inserted)
                it->second++;
        }

        std::vector<std::pair<int, int>> num_counts;
        for (const auto &[num, count] : counts)
            if (count)
                num_counts.push_back({num, count});

        std::vector<std::vector<int>> result;
        std::vector<int> buf;
        backtrack(result, buf, num_counts, 0, target);
        return result;
    }

public:
    std::vector<std::vector<int>> combinationSum2(const std::vector<int> &nums, int target) { return sol(nums, target); }
};