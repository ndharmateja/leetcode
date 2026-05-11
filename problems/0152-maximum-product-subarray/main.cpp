#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP solution
     * Theta(n) time and Theta(n) space solution
     */
    static int sol1(const std::vector<int> &nums)
    {
        /**
         * * DP Solution
         * dp_min[i]: the min product of a contiguous subarray ending at index i
         * dp_max[i]: the max product of a contiguous subarray ending at index i
         * * Base case
         * dp_min[0] = nums[0]
         * dp_max[0] = nums[0]
         * * Recurrence relation
         * We need to store both the min and max as a negative value min product so far
         * can multiply with a current negative value in the nums array to produce a
         * value that is positive
         * If the current number is smaller than the dp_min[i] * nums[i] or dp_max[i] * nums[i]
         * then it is better to start a new sequence whose product is smallest including
         * just the current number
         * Similarly with the positive direction
         * dp_min[i] = min{ dp_min[i] * nums[i], dp_max[i] * nums[i], nums[i] }
         * dp_max[i] = max{ dp_min[i] * nums[i], dp_max[i] * nums[i], nums[i] }
         * * Order of filling
         * From left to right as dp values at i only depend upon the dp values at i-1
         * * Final answer
         * max{ dp_max[i] for i in [0, n-1] }
         * as the contiguous subarray can end at any index
         * So instead of having to do an extra loop at the end, we can keep track
         * of the global max product as we compute each dp_max[o]
         * * Running time
         * #subproblems = n
         * Work per subproblem = Theta(1)
         * Postprocessing = Theta(1)
         * Total running time = Theta(n)
         */
        // Init the dp arrays
        int n{static_cast<int>(nums.size())};
        std::vector<int> dp_min{n}, dp_max{n};

        // Base case values
        dp_min[0] = dp_max[0] = nums.front();
        int max_product{nums.front()}, product1, product2;

        // Fill the DP table from left to right
        for (int i = 1; i < n; i++)
        {
            product1 = dp_min[i - 1] * nums[i];
            product2 = dp_max[i - 1] * nums[i];
            dp_min[i] = std::min({product1, product2, nums[i]});
            dp_max[i] = std::max({product1, product2, nums[i]});
            max_product = std::max(dp_max[i], max_product);
        }

        // Return the answer
        return max_product;
    }

    /**
     * Space optimized version of solution1
     * Theta(n) time and Theta(1) space solution
     */
    static int sol2(const std::vector<int> &nums)
    {
        /**
         * Explanation:
         * Instead of storing the 2 whole arrays dp_min and dp_max
         * we only store the dp_min[i-1] and dp_max[i-1] as we only need them
         * to calculate the dp_min[i] and dp_max[i]
         */
        int n{static_cast<int>(nums.size())};
        int min{nums.front()}, max{nums.front()};

        // Base case values
        int max_product{max}, product1, product2;
        for (int i = 1; i < n; i++)
        {
            product1 = min * nums[i];
            product2 = max * nums[i];
            min = std::min({product1, product2, nums[i]});
            max = std::max({product1, product2, nums[i]});
            max_product = std::max(max, max_product);
        }
        return max_product;
    }

public:
    int maxProduct(const std::vector<int> &nums) { return sol2(nums); }
};