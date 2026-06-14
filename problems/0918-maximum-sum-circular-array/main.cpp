#include <vector>

class Solution
{
private:
    /**
     * Space optimized DP solution to find the sum of the max subarray
     * (not circular)
     * Refer to solution 2 of problem 53 for more details
     *
     * Theta(n) time and Theta(1) space complexity
     */
    static int max_subarray_sum(const std::vector<int> &nums)
    {
        // We only need the previous value to compute the current value
        // and we can store the global max value in a new variable
        // and we can update it accordingly as we keep calculating the dp values
        int n{static_cast<int>(nums.size())};
        int prev_max{nums[0]}, global_max{prev_max};

        // Do the computations from left to right
        // Invariant: At the start of iteration 'i', prev_max keeps track of the
        // max subarray sum ending at index 'i-1'
        for (int i = 1; i < n; i++)
        {
            prev_max = std::max(prev_max + nums[i], nums[i]);
            global_max = std::max(global_max, prev_max);
        }

        // Return the max value in the dp array
        return global_max;
    }

    /**
     * Theta(n) time and Theta(n) space
     */
    static int max_subarray_sum_wrapped(const std::vector<int> &nums)
    {
        // prefix_sums[i]: sum of all the values in nums[:i+1] (including index i)
        // suffix_sums[i]: sum of all the values in nums[i:] (including index i)
        int n{static_cast<int>(nums.size())};
        std::vector<int> prefix_sums(n);
        std::vector<int> suffix_sums(n);

        // Fill the prefix and suffix sums arrays
        int curr_sum{nums.front()};
        prefix_sums.front() = nums.front();
        for (int i = 1; i < n; i++)
        {
            curr_sum += nums[i];
            prefix_sums[i] = curr_sum;
        }
        curr_sum = nums.back();
        suffix_sums.back() = nums.back();
        for (int i = n - 2; i >= 0; i--)
        {
            curr_sum += nums[i];
            suffix_sums[i] = curr_sum;
        }

        // Find the max values so far in the prefix sums and suffix sums
        // Eg:
        // prefix_sums = {4, 5, 2, 7, 5} => max values so far = {4, 5, 5, 7, 7}
        // suffix_sums = {4, 5, 2, 7, 5} => max values so far = {7, 7, 7, 7, 5}
        int max_so_far = prefix_sums.front();
        for (int i = 1; i < n; i++)
        {
            max_so_far = std::max(max_so_far, prefix_sums[i]);
            prefix_sums[i] = max_so_far;
        }
        max_so_far = suffix_sums.back();
        for (int i = n - 2; i >= 0; i--)
        {
            max_so_far = std::max(max_so_far, suffix_sums[i]);
            suffix_sums[i] = max_so_far;
        }

        // We want to maximize the sum of a prefix and a suffix
        // such that the prefix ends before the suffix starts to find the max
        // subarray sum that is wrapped around and such that the
        // prefix and suffix are non-empty
        max_so_far = std::numeric_limits<int>::min();
        for (int i = 1; i < n - 1; i++)
            max_so_far = std::max(max_so_far,
                                  std::max(prefix_sums[i - 1] + suffix_sums[i],
                                           prefix_sums[i] + suffix_sums[i + 1]));

        // Return the answer
        return max_so_far;
    }

    /**
     * Theta(n) time and Theta(n) space
     */
    static int
    sol1(const std::vector<int> &nums) { return std::max(max_subarray_sum(nums),
                                                         max_subarray_sum_wrapped(nums)); }

    /**
     * Theta(n) time and Theta(1) space
     *
     * Refer to solution 2 of problem 53 for more details
     */
    static int sol2(const std::vector<int> &nums)
    {
        // We only need the previous value to compute the current value
        // and we can store the global max value in a new variable
        // and we can update it accordingly as we keep calculating the dp values
        int n{static_cast<int>(nums.size())};
        int prev_max{nums[0]}, global_max{prev_max};
        int prev_min{nums[0]}, global_min{prev_min};
        int total_sum{nums[0]};

        // Run Kadane's algorithm to find the minimum subarray sum
        // and the maximum subarray sum
        // As the wrapped around sum will be maximum if the leftover part
        // if the middle chunk (leftover after taking the wraparound) is minimum
        // So the max wrapped around subarray sum = total sum - min subarray sum
        for (int i = 1; i < n; i++)
        {
            int curr = nums[i];
            prev_max = std::max(prev_max + curr, curr);
            global_max = std::max(global_max, prev_max);

            prev_min = std::min(prev_min + curr, curr);
            global_min = std::min(global_min, prev_min);

            total_sum += curr;
        }

        // TODO: explain edge cases
        if (global_max < 0)
            return global_max;

        // Return the max value in the dp array
        return std::max(global_max, total_sum - global_min);
    }

public:
    int maxSubarraySumCircular(const std::vector<int> &nums) { return sol2(nums); }
};