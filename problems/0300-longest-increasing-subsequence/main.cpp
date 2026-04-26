#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP approach
     *
     * Theta(n^2) time and Theta(n) space solution
     */
    int solution1(const std::vector<int> &nums)
    {
        // DP solution:
        // dp[i]: length of the longest strictly increasing subsequence *ending* at index i
        // Base case:
        // dp[0] = 1
        // Recurrence relation:
        // dp[i] = max{dp[j] s.t. j < i and nums[j] < nums[i]} + 1
        // Order of filling the table:
        // from left to right as we only need the left side values
        // Final answer:
        // max{dp[i] s.t. 0 <= i <= n-1}
        int n{static_cast<int>(nums.size())};
        std::vector<int> dp(n);

        // Base case
        dp[0] = 1;

        // Fill the dp table from left right
        for (int i = 1; i < n; i++)
        {
            // Find the max dp value for j in the [0, i-1] range such that nums[j] < nums[i]
            // We can start with a max_value as 0 as each value in the dp array will be atleast 1
            int max_value = 0;
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i] && dp[j] > max_value)
                    max_value = dp[j];

            // If the max value is 0 it means that there are no smaller elements than nums[i]
            // in the range [0, i-1] in which case dp[i] = 1 as this is the length of the LIS
            // ending here with just nums[i]
            // Either way, we can use max_value + 1
            dp[i] = max_value + 1;
        }

        // Return the result
        return *std::max_element(dp.begin(), dp.end());
    }

    /**
     * TODO: Theta(n log n) solution using binary search and patience sorting
     */
    int solution2(const std::vector<int> &nums) {}

public:
    int lengthOfLIS(const std::vector<int> &nums) { return solution1(nums); }
};