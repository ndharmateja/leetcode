#include <vector>
#include <map>

class Solution
{
    static void backtrack(std::vector<std::vector<int>> &result, std::vector<int> &buf,
                          std::vector<std::pair<int, int>> &nums_counts,
                          const int min_index, const int num_candidates_left)
    {
        result.push_back(buf);

        if (!num_candidates_left)
            return;

        for (size_t i = min_index; i < nums_counts.size(); ++i)
        {
            auto &[num, count] = nums_counts[i];
            if (!count)
                continue;

            buf.push_back(num);
            count--;
            backtrack(result, buf, nums_counts, i, num_candidates_left - 1);
            count++;
            buf.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums)
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
        backtrack(result, buf, num_counts, 0, nums.size());
        return result;
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) { return sol(nums); }
};