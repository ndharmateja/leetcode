#include <vector>

class Solution
{
private:
    /**
     * Iterative version of solution3:
     * At each stage we add the current element to each of the subsets
     * and add them all to S
     *
     * Eg: nums = {A, B, C}
     * Initially         : S = {{}}
     * after processing A: S = {{}, {A}}
     * after processing B: S = {{}, {A}, {B}, {A, B}}
     * after processing C: S = {{}, {A}, {B}, {A, B}, {C}, {A, C}, {B, C}, {A, B, C}}
     */
    static std::vector<std::vector<int>> sol(const std::vector<int> &nums)
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
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums) { return sol(nums); };
};