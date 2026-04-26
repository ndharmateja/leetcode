#include <vector>
#include <algorithm>
#include <utility>

class Solution
{
private:
    /**
     * Finds the pair of indices which add up to the target in the nums vector
     * which is sorted
     * See problem 167 for the invariant proof
     */
    static std::pair<int, int> two_sum_sorted(const std::vector<int> &nums, int lo, int hi, int target)
    {
        while (lo < hi)
        {
            // If the sum of values at lo and hi is smaller than the target
            // then we increment the left pointer
            int sum = nums[lo] + nums[hi];
            if (sum < target)
                lo++;

            // If the sum of values at lo and hi is greater than the target
            // then we decrement the right pointer
            else if (sum > target)
                hi--;

            // If the sum of values at lo and hi is equal to the target
            // we found the solution
            else
                return {lo, hi};
        }

        // Since there always exists a solution, we would never reach here
        return {-1, -1};
    }

    static std::vector<std::vector<int>> solution1(std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end());

        int i = 0;
        while (i < n - 2)
        {
            // Find all the pairs of numbers that add up to -nums[i] so that the
            // triplet adds up to 0
            int lo = i + 1, hi = n - 1;
            while (true)
            {
                // Use the two sum function to find two numbers in the range [lo, hi]
                // that add up to -nums[i] so that the triplet adds up to 0
                // Since we sorted the array, the two sum function will find a solution
                // if it exists in O(n) time or returns {-1, -1} if it doesn't exist
                auto [left_index, right_index] = two_sum_sorted(nums, lo, hi, -nums[i]);
                if (left_index == -1)
                    break;

                // Create the triplet and add to the result
                std::vector<int> triplet{nums[i], nums[left_index], nums[right_index]};
                result.push_back(triplet);

                // Now the search range for the new triplet is [left_index + 1, right_index - 1]
                // We should not add duplicate triplets, so we need to skip all the duplicates
                // so we keep moving the left pointer until it points to a different number
                // and the right pointer until it points to a different number

                // Idea: probably binary search to find the next different number
                // The binary search helps only if there are a lot of duplicates
                // otherwise just moving the pointers would be good enough
                // and we have cache locality

                // Update the new lo to left_index + 1
                // Move lo such that it points to a different number than nums[left_index]
                lo = left_index + 1;
                int lo_num = nums[left_index];
                while (lo < n && nums[lo] == lo_num)
                    lo++;

                // Update the new hi to right_index - 1
                // Move hi such that it points to a different number than nums[right_index]
                // We can stop if hi equals lo because we don't need to move any further
                hi = right_index - 1;
                int hi_num = nums[right_index];
                while (hi > lo && nums[hi] == hi_num)
                    hi--;

                // We can break directly here if lo == hi as we want distinct triplets
                // so if lo == hi then there won't be two distinct elements in that range
                if (lo == hi)
                    break;
            }

            // There shouldn't be any duplicate triplets
            // So we can move i such that it points to a different number than the one
            // we already found the triplets for as the first number
            // Move i such that it is not the same as nums[i] because we already covered triplets
            // as nums[i] as the first number
            int i_num = nums[i];
            while (i < n - 2 && nums[i] == i_num)
                i++;
        }

        // Return the result
        return result;
    }

public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) { return solution1(nums); }
};
