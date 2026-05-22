#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Bottom up DP approach
     *
     * Theta(n^2) time and Theta(n) space sol
     */
    int sol1(const std::vector<int> &nums)
    {
        // DP sol:
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
     * Returns the index of the smallest number in the dp array
     * that is >= than num
     *
     * Preconditions:
     * 1. dp is a sorted array in ascending order with unique elements
     * 2. num > dp.front() (so the answer won't be 0)
     * 3. num < dp.back()  (the answer still can be dp.size() - 1)
     *
     * Because of the invariant we can infer that there are going to be atleast
     * 3 elements in the given dp array
     */
    int binary_search(const std::vector<int> &dp, int num)
    {
        // Init the pointers and the result
        // n-1 is a potential candidate as num < dp.back() but we use binary search
        // to find a better candidate
        int lo{1}, hi{static_cast<int>(dp.size()) - 1}, mid;
        int result{hi};

        // Run binary search as long as the binary search range is valid
        while (lo <= hi)
        {
            // If we found the given num in the dp array, that is the answer
            // as we have unique elements and if there is a matching number
            // that is the smallest number >= given number
            mid = lo + (hi - lo) / 2;
            if (dp[mid] == num)
                return mid;

            // If dp[mid] > num, then this is a better candidate solution than
            // what we have stored in result currently
            // So we update the result and see if there is an even better solution
            // in the left half
            if (dp[mid] > num)
            {
                result = mid;
                hi = mid - 1;
            }

            // If the mid index is not a valid candidate then we go right
            // looking for a better candidate
            else
                lo = mid + 1;
        }

        // Return the result
        return result;
    }

    /**
     * Solution using patience sorting and binary search
     *
     * Theta(n log n) time in the worst case (Every binary search takes full depth)
     * Theta(n) space (as we are reserving the dp array with size n)
     */
    int sol2(const std::vector<int> &nums)
    {
        // Init the dp array and reserve it to the size of 'n'
        // Even though the dp array could be much smaller we are reserving
        // the worst case space to avoid reallocations
        int n{static_cast<int>(nums.size())};
        std::vector<int> dp;
        dp.reserve(n);

        /**
         * Invariants of the DP array
         * 1. dp[i] is the smallest number from the nums vector that ends in an increasing
         *   subsequence of length 'i+1' from the numbers processed so far
         * 2. With all the numbers processed so far, the length of the longest increasing
         *   subsequence has length dp.size()
         * 3. The numbers in the dp array are unique and sorted in ascending order
         */

        // Initially we can add the first number directly
        // The invariants still hold true
        dp.push_back(nums.front());

        // For each of the numbers from i = 1 to i = n-1
        for (int i = 1; i < n; ++i)
        {
            // If the current number is equal to any of the numbers in the DP array
            // we can directly replace it as the condition is exactly satisfied

            // If the current number <= the first number in the dp array
            // it means the number goes at index 0
            int num = nums[i];
            if (num <= dp.front())
                dp[0] = num;

            // If the number equals the last number we can replace the number
            // which is essentially doing nothing, so we can continue
            else if (num == dp.back())
                continue;

            // If the number is greater than the last number than this number
            // we can append it to the end of the DP array
            else if (num > dp.back())
                dp.push_back(num);

            // If any of the edge cases aren't matched
            // then num > dp.front() and num < dp.back()
            // which means we can do a binary search to find which number to replace
            // and the answer index is going to be in [1, dp.size() - 1]
            else
                dp[binary_search(dp, num)] = num;
        }

        // According to the invariant
        return dp.size();
    }

public:
    int lengthOfLIS(const std::vector<int> &nums) { return sol2(nums); }
};

int main()
{
    Solution().lengthOfLIS({0, 1, 0, 3, 2, 3});
}