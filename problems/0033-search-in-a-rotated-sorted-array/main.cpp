#include <iostream>
#include <vector>

class Solution
{
private:
    // Check main.cpp in problem 153 for more details and documentation
    static int find_min_index(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid;
        int min_value{nums[lo]}, min_value_index{lo};

        while (lo <= hi)
        {
            if (nums[lo] < nums[hi] && nums[lo] < min_value)
                return lo;

            mid = lo + (hi - lo) / 2;
            if (nums[mid] < min_value)
            {
                min_value = nums[mid];
                min_value_index = mid;
            }

            if (nums[mid] < nums[hi])
                hi = mid - 1;

            else
                lo = mid + 1;
        }

        return min_value_index;
    }

    /**
     * Regular binary search
     * Theta(log n) time and Theta(1) space in worst case
     * Note: it does 2 passes, one to find the min index and one to find the target.
     */
    static int binary_search(const std::vector<int> &nums, int lo, int hi, int target)
    {
        int mid;
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            if (target < nums[mid])
                hi = mid - 1;
            else if (target > nums[mid])
                lo = mid + 1;
            else
                return mid;
        }
        return -1;
    }

    static int solution1(const std::vector<int> &nums, int target)
    {
        // Base case of 1 element
        int n{static_cast<int>(nums.size())};
        if (n == 1)
            return target == nums[0] ? 0 : -1;

        // If there is no rotation, then we can directly do a binary search
        if (nums[0] < nums[n - 1])
            return binary_search(nums, 0, n - 1, target);

        // Find the drop point in the rotated array
        int min_index{find_min_index(nums)};

        // If the target is between the values nums[0] and nums[min_index-1]
        // we search in the first part
        int result;
        if ((nums[0] <= target && target <= nums[min_index - 1]) &&
            (result = binary_search(nums, 0, min_index - 1, target)) != -1)
            return result;

        // If we reach here then either the target isn't between nums[0] and nums[min_index-1]
        // or it is not in the first part
        // So we look for the target in the second half
        // We can directly return the result of the second part as there are no
        // more parts to check
        if (nums[min_index] <= target && target <= nums[n - 1])
            return binary_search(nums, min_index, n - 1, target);

        // If we reach here, it means that the target is not in both the ranges
        // so we can directly return -1
        return -1;
    }

    /**
     * One pass binary search solution
     * Theta(log n) time and Theta(1) space in the worst case
     */
    static int solution2(const std::vector<int> &nums, int target)
    {
        int n{static_cast<int>(nums.size())}, lo{0}, hi{n - 1}, mid;
        while (lo <= hi)
        {
            // If nums[lo] < nums[hi], then we can do a normal binary search
            // which doesn't do as many checks as this version of binary search.
            // Even if we didn't have this optimization, the code still works
            // as it goes into the case of nums[lo] <= nums[mid].
            if (nums[lo] < nums[hi])
                return binary_search(nums, lo, hi, target);

            // At this point we know that the drop point is part of the [lo, hi] range
            mid = lo + (hi - lo) / 2;

            // If the value at mid matches target, we can exit
            if (target == nums[mid])
                return mid;

            // At any stage, when the drop point is part of the range, either the
            // left range of mid or right range of mid is sorted (there could be a case
            // where both left and right are sorted without rotations)
            // When mid = min_index (the drop point), both sides are sorted.

            // If left range is sorted and target is in that range we go left
            // otherwise go right
            // If left range is sorted
            if (nums[lo] <= nums[mid])
            {
                // and target is in the left range, go left
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;
                // otherwise go right
                else
                    lo = mid + 1;
            }
            // If the right range is sorted
            else
            {
                // and target is in the right range, go right
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;
                // otherwise go left
                else
                    hi = mid - 1;
            }
        }

        // If we reach here it means that target isn't there in nums
        return -1;
    }

public:
    int search(std::vector<int> &nums, int target) { return solution2(nums, target); }
};