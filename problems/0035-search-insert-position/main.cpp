#include <vector>

class Solution
{
private:
    /**
     * Binary search using candidate variable pattern.
     * Theta(log n) time and Theta(1) space in worst case
     */
    static int solution1(const std::vector<int> &nums, int target)
    {
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid, answer{n};

        // Find the index of the first number >= target
        // and that index is the insertion index of target
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            if (target < nums[mid])
            {
                // Then the insertion point is in the left half
                // and mid is a better insertion point
                answer = mid;
                hi = mid - 1;
            }
            else if (target > nums[mid])
            {
                // Then the insertion point is in the right half
                // but mid is not a potential insertion point
                lo = mid + 1;
            }
            else
            {
                // Since the target is found and all the values in nums are distinct
                // mid is the index of insertion point
                answer = mid;
                break;
            }
        }

        return answer;
    }

public:
    int searchInsert(const std::vector<int> &nums, int target) { return solution1(nums, target); }
};