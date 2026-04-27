#include <vector>

class Solution
{
private:
    /**
     * Calculates the max money a robber can rob in the range of houses [lo, hi]
     * such that no two consecutive houses are robbed (House Robber 1 problem)
     *
     * See problem 198 for more details.
     */
    static int solution(const std::vector<int> &nums, int lo, int hi)
    {
        // Edge cases
        int n{hi - lo + 1};
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[lo];
        if (n == 2)
            return std::max(nums[lo], nums[lo + 1]);

        // Init values
        int prev2 = nums[lo], prev1 = std::max(nums[lo], nums[lo + 1]), curr;

        // Fill the table
        for (int i = lo + 2; i <= hi; i++)
        {
            curr = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }

        // Return the result
        return curr;
    }

public:
    int rob(std::vector<int> &nums)
    {
        // Edge cases
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);

        // Either house 0 is robbed or not,
        // If the house 0 is robbed, then houses 1 and n-1 can't be robbed
        // so the max total robbed would be nums[0] + max(2, n-2)
        // If the house 0 is not robbed, then any house from 1 to n-1 can be robbed
        // so the max total robbed would be max(1, n-1)
        // So we take the max between the two
        return std::max(nums[0] + solution(nums, 2, n - 2),
                        solution(nums, 1, n - 1));
    }
};