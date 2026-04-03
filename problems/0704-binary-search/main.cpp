#include <iostream>
#include <vector>

class Solution
{
private:
    /**
     * Recursive binary search solution
     * Theta(log n) time and Theta(log n) space (for recursion)
     */
    static int solution1(const std::vector<int> &nums, int target) { return solution1(nums, target, 0, nums.size() - 1); }
    static int solution1(const std::vector<int> &nums, int target, int lo, int hi)
    {
        if (lo > hi)
            return -1;
        int mid = lo + (hi - lo) / 2;
        if (target < nums[mid])
            return solution1(nums, target, lo, mid - 1);
        if (target > nums[mid])
            return solution1(nums, target, mid + 1, hi);
        return mid;
    }

    /**
     * Iterative binary search solution
     * Theta(log n) time and Theta(1) space
     */
    static int solution2(const std::vector<int> &nums, int target)
    {
        int lo{0}, hi{static_cast<int>(nums.size() - 1)}, mid;
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

        // If we reach here that means that lo has crossed hi
        // and we didn't find the target
        return -1;
    }

public:
    int search(const std::vector<int> &nums, int target) { return solution1(nums, target); }
};