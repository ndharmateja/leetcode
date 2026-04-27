#include <vector>
#include <algorithm>

class Solution
{
    /**
     * Bottom up DP approach
     *
     * Theta(n) time and Theta(n) space complexity
     */
    static int solution1(const std::vector<int> &nums)
    {
        // * DP solution:
        // dp[i]: max subarray sum ending at index[i]
        // * Base case:
        // dp[0] = nums[0]
        // * Recurrence relation
        // If the max sum upto index i-1 is negative, then we should only
        // consider the number nums[i] without adding anything from before
        // otherwise we add the sum of dp[i-1] to extend it with nums[i]
        // dp[i] = nums[i]            if dp[i-1] < 0
        //       = dp[i-1] + nums[i]  otherwise
        // * Order of filling
        // We will it from left to right as we only need the left value at
        // each point
        // * Final answer
        // max{dp[i] for 0 <= i <= n-1} as the max contiguous subarray
        // can end anywhere in the array
        int n{static_cast<int>(nums.size())};
        std::vector<int> dp(n);

        // Base case
        dp[0] = nums[0];

        // Fill the table from left to right
        for (int i = 1; i < n; i++)
            dp[i] = (dp[i - 1] <= 0 ? 0 : dp[i - 1]) + nums[i];

        // Return the max value in the dp array
        return *std::max_element(dp.begin(), dp.end());
    }

    /**
     * Space optimized version of solution 1
     *
     * Theta(n) time and Theta(1) space complexity
     */
    static int solution2(const std::vector<int> &nums)
    {
        // We only need the previous value to compute the current value
        // and we can store the global max value in a new variable
        // and we can update it accordingly as we keep calculating the dp values
        int n{static_cast<int>(nums.size())};
        int prev{nums[0]}, max_value{prev}, curr;

        // Do the computations from left to right
        for (int i = 1; i < n; i++)
        {
            curr = (prev <= 0 ? 0 : prev) + nums[i];
            if (curr > max_value)
                max_value = curr;
            prev = curr;
        }

        // Return the max value in the dp array
        return max_value;
    }

    /**
     * Divide and Conquer approach
     *
     * Theta(n log n) time and Theta(log n) space (for recursion)
     */
    static int solution3(const std::vector<int> &nums, int lo, int hi)
    {
        // Base cases
        if (lo > hi)
            return 0;
        if (lo == hi)
            return nums[lo];

        // The max subarray can be of three types:
        // 1. completely contained in the left subarray
        // 2. completely contained in the right subarray
        // 3. spans both the left and right subarrays
        // 1 and 2 can be recursively computed
        // The cross subarray sum can be divided into two parts:
        // suffix of the left subarray and the prefix of the right subarray
        // and each of them have to be maximum individually for the result to be
        // maximum. Otherwise it would be a contradiction as if there were a
        // even higher prefix/suffix sum than corresponding to the max cross subarray sum
        // then we could use that to make the resulting max cross subarray sum higher
        // which is a contradiction.
        // The recurrence relation is T(n) = 2T(n/2) + Theta(n)
        // so the running time becomes Theta(n log n) by master's theorem

        // Recursively compute the left and right max subarray sums
        int mid = lo + (hi - lo) / 2;
        int left_sum = solution3(nums, lo, mid);
        int right_sum = solution3(nums, mid + 1, hi);

        // Find the max cross subarray sum
        int cross_sum = max_suffix_sum(nums, lo, mid) + max_prefix_sum(nums, mid + 1, hi);

        // Return the max among the 3 sums
        return std::max({left_sum, right_sum, cross_sum});
    }

    static int solution3(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        return solution3(nums, 0, n - 1);
    }

    static int max_prefix_sum(const std::vector<int> &nums, int lo, int hi)
    {
        int curr_sum{nums[lo]}, max_sum{curr_sum};
        for (int i = lo + 1; i <= hi; i++)
        {
            curr_sum += nums[i];
            if (curr_sum > max_sum)
                max_sum = curr_sum;
        }
        return max_sum;
    }

    static int max_suffix_sum(const std::vector<int> &nums, int lo, int hi)
    {
        int curr_sum{nums[hi]}, max_sum{curr_sum};
        for (int i = hi - 1; i >= lo; i--)
        {
            curr_sum += nums[i];
            if (curr_sum > max_sum)
                max_sum = curr_sum;
        }
        return max_sum;
    }

    struct Result
    {
        int total_sum;
        int max_prefix_sum;
        int max_suffix_sum;
        int max_subarray_sum;
    };

    /**
     * Another divide and Conquer approach
     *
     * Theta(n) time and Theta(log n) space (for recursion)
     * Recurrence relation is T(n) = 2T(n/2) + Theta(1)
     */
    static Result solution4(const std::vector<int> &nums, int lo, int hi)
    {
        // Base cases
        if (lo > hi)
            return {0, 0, 0, 0};
        if (lo == hi)
            return {nums[lo], nums[lo], nums[lo], nums[lo]};

        // Find the results recursively on the left and right subarrays
        int mid = lo + (hi - lo) / 2;
        Result left = solution4(nums, lo, mid);
        Result right = solution4(nums, mid + 1, hi);

        // Calculate the resulting values for the total array using the values
        // from the left and right subarrays
        Result total;
        total.total_sum = left.total_sum + right.total_sum;
        total.max_prefix_sum = std::max(left.max_prefix_sum,
                                        left.total_sum + right.max_prefix_sum);
        total.max_suffix_sum = std::max(right.max_suffix_sum,
                                        left.max_suffix_sum + right.total_sum);
        total.max_subarray_sum = std::max({left.max_subarray_sum,
                                           right.max_subarray_sum,
                                           left.max_suffix_sum + right.max_prefix_sum});
        return total;
    }

    static int solution4(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        return solution4(nums, 0, n - 1).max_subarray_sum;
    }

public:
    int maxSubArray(const std::vector<int> &nums) { return solution4(nums); }
};