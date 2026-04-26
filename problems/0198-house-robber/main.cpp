#include <vector>
#include <utility>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP approach using 2 1D arrays
     *
     * Theta(n) time and Theta(n) space complexity
     * where n = number of houses
     */
    static int solution1(const std::vector<int> &nums)
    {
        // Edge cases
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);

        // DP solution:
        // including[i]: the max amount a robber can steal from houses 0 to i including house i
        // excluding[i]: the max amount a robber can steal from houses 0 to i excluding house i
        //
        // Base cases:
        // including[0] = nums[0]
        // excluding[0] = 0
        // including[1] = nums[1]
        // excluding[1] = nums[0]
        //
        // Recurrence:
        // To choose house 'i', we should not include house 'i-1' and then add nums[i]
        // or we can include house 'i-1' and not add nums[i]
        // including[i] = max{including[i-1], excluding[i-1] + nums[i]}
        // excluding[i] = max{including[i-1], excluding[i-1]}
        //
        // Order of filling:
        // We fill the 2 arrays from left to right
        //
        // Final answer:
        // The max amount from houses 0 to n including or excluding the last house
        // max{including[n-1], excluding[n-1]}
        std::vector<int> including(n);
        std::vector<int> excluding(n);

        // Base case
        including[0] = nums[0];
        excluding[0] = 0;
        including[1] = nums[1];
        excluding[1] = nums[0];

        // Fill the table
        for (int i = 2; i < n; i++)
        {
            including[i] = std::max(including[i - 1], excluding[i - 1] + nums[i]);
            excluding[i] = std::max(including[i - 1], excluding[i - 1]);
        }

        // Return the result
        return std::max(including[n - 1], excluding[n - 1]);
    }

    /**
     * Space optimized version of solution1
     *
     * Theta(n) time and Theta(1) space complexity
     * where n = number of houses
     */
    static int solution2(const std::vector<int> &nums)
    {
        // Edge cases
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);

        // Base case for i = 1
        int prev_including{nums[1]}, prev_excluding{nums[0]}, curr_including, curr_excluding;

        // Fill the table
        for (int i = 2; i < n; i++)
        {
            curr_including = std::max(prev_including, prev_excluding + nums[i]);
            curr_excluding = std::max(prev_including, prev_excluding);
            prev_including = curr_including;
            prev_excluding = curr_excluding;
        }

        // Return the result
        return std::max(curr_including, curr_excluding);
    }

    /**
     * Bottom up DP solution using one array
     *
     * Theta(n) time and Theta(n) space complexity
     * where n = number of houses
     */
    static int solution3(const std::vector<int> &nums)
    {
        // Edge cases
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);

        // DP solution:
        // dp[i]: the max amount a robber can steal from houses 0 to i
        //
        // Base cases:
        // dp[0] = nums[0]
        // dp[1] = max{nums[0], nums[1]}
        //
        // Recurrence:
        // dp[i] = max{dp[i-1], dp[i-2] + nums[i]}
        //
        // Order of filling:
        // We fill the array from left to right
        //
        // Final answer:
        // dp[n-1]
        std::vector<int> dp(n);

        // Base case
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        // Fill the table
        for (int i = 2; i < n; i++)
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);

        // Return the result
        return dp[n - 1];
    }

    /**
     * Space optimized version of solution3
     *
     * Theta(n) time and Theta(1) space complexity
     * where n = number of houses
     */
    static int solution4(const std::vector<int> &nums)
    {
        // Edge cases
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);

        // Init values
        int prev2 = nums[0], prev1 = std::max(nums[0], nums[1]), curr;

        // Fill the table
        for (int i = 2; i < n; i++)
        {
            curr = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }

        // Return the result
        return curr;
    }

public:
    int rob(const std::vector<int> &nums) { return solution4(nums); }
};