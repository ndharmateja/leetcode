#include <iostream>
#include <vector>

class Solution
{
private:
    /**
     * Finds an index where target and does linear scan towards both sides
     * to find the range
     * Theta((log n) + k) time and Theta(1) space
     * where k = #repetitions of the element
     * and could potentially run in Theta(n) if all the elements are the target
     */
    static std::vector<int> solution1(const std::vector<int> &nums, int target)
    {
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid;
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            if (target < nums[mid])
                hi = mid - 1;
            else if (target > nums[mid])
                lo = mid + 1;
            else
                break;
        }

        // At this point either nums[mid] == target in which case we need to find the range
        // or lo > hi in which case the target doesn't exist in nums
        if (lo > hi)
            return {-1, -1};

        // Make lo and hi as mid and linearly expand the range to find the whole range of target
        lo = hi = mid;
        while (lo > 0 && nums[lo - 1] == target)
            lo--;
        while (hi < n - 1 && nums[hi + 1] == target)
            hi++;

        // Return the range
        return {lo, hi};
    }

    /**
     * Does a dual binary search to find the lowest index with the target
     * and the highest index with the target independently
     *
     * Theta(log n) time and Theta(1) space
     */
    static std::vector<int> solution2(const std::vector<int> &nums, int target)
    {
        // Find the lower end of the range
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid;
        while (lo <= hi)
        {
            // Find the mid index
            mid = lo + (hi - lo) / 2;

            // If the target is smaller than the middle element
            // we can look for the lower end in the left half
            if (target < nums[mid])
                hi = mid - 1;

            // Similarly if the target is greater than the middle element
            // we can look for the lower end in the right half
            else if (target > nums[mid])
                lo = mid + 1;

            // At this point, the target is equal to the middle element
            // If the middle element is the starting value in the target range
            // we can exit early as we found the starting range of the target
            else if (mid == 0 || nums[mid - 1] < target)
                break;

            // If the middle element is not the starting range of the target
            // we know it is going to be in the left half
            else
                hi = mid - 1;
        }

        // If at this point, lo > hi, it means that target doesn't exist
        if (lo > hi)
            return {-1, -1};

        // At this point we know that target exists
        // and mid keeps track of the left end of the range
        int range_start{mid};

        // Find the upper end of the range
        lo = 0, hi = n - 1;
        while (lo <= hi)
        {
            // Find the mid index
            mid = lo + (hi - lo) / 2;

            // If the target is smaller than the middle element
            // we can look for the lower end in the left half
            if (target < nums[mid])
                hi = mid - 1;

            // Similarly if the target is greater than the middle element
            // we can look for the lower end in the right half
            else if (target > nums[mid])
                lo = mid + 1;

            // At this point, the target is equal to the middle element
            // If the middle element is the ending value in the target range
            // we can exit early as we found the ending range of the target
            else if (mid == n - 1 || nums[mid + 1] > target)
                break;

            // If the middle element is not the ending range of the target
            // we know it is going to be in the right half
            else
                lo = mid + 1;
        }

        // At this point mid keeps track of the right end of the range
        return {range_start, mid};
    }

    /**
     * This solution is very similar to solution 2 but doesn't do an early exit
     * even if we found the target's lower/upper end. It goes all the way until
     * it narrows to one element (lo = hi). The code is cleaner though.
     * Asymptotically same running time and space complexity as solution 2
     */
    static std::vector<int> solution3(const std::vector<int> &nums, int target)

    {
        // Find the lower end of the range
        // Eg: initial range of data: [5, 7, 7, 8, 8, 10] => lo = 0, hi = 5
        // - mid = 2, as target > nums[mid] => we go to the right => lo = 3, hi = 5
        // - mid = 4, as target == nums[mid]. even though the target matched we don't stop searching
        // as there could be more of the target in the left. so we make our new search range [lo, mid].
        // we include mid as well in the search range because mid might be the answer
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid;
        while (lo <= hi)
        {
            // This is a left biased mid index (in case of even #elements
            // in the [lo, hi] range)
            mid = lo + (hi - lo) / 2;
            if (target < nums[mid])
                hi = mid - 1;
            else if (target > nums[mid])
                lo = mid + 1;
            else if (lo < hi)
                hi = mid;
            else
                break;
        }

        // If at this point, lo > hi, it means that target doesn't exist
        if (lo > hi)
            return {-1, -1};

        // At this point we know that target exists
        // and mid keeps track of the left end of the range
        int range_start{mid};

        // Find the upper end of the range
        lo = 0, hi = n - 1;
        while (lo <= hi)
        {
            // This is a right biased mid index (in case of even #elements
            // in the [lo, hi] range)
            // If we don't use a right biased mid index, if there are two elements
            // and the element at lo is the target. and hi = lo + 1 as there are only
            // two elements and mid also is low and we look for the right end in [mid, hi]
            // which is the same as [lo, hi]. It goes into an infinite loop
            mid = hi - (hi - lo) / 2;
            if (target < nums[mid])
                hi = mid - 1;
            else if (target > nums[mid])
                lo = mid + 1;
            else if (lo < hi)
                lo = mid;
            else
                break;
        }

        // At this point mid keeps track of the right end of the range
        return {range_start, mid};
    }

public:
    std::vector<int> searchRange(const std::vector<int> &nums, int target) { return solution3(nums, target); }
};