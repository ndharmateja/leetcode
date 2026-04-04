#include <vector>
#include <limits>

class Solution
{
public:
    /**
     * Binary search using candidate variable pattern
     * Theta(log n) time and Theta(1) space in worst case
     */
    int findMin(std::vector<int> &nums)
    {
        // Min value is the first value in the right section
        //    .
        //   .
        //  .
        // .
        //             .
        //            .
        //           .
        //          .
        //         .
        //        .
        //       .
        //      .
        int n{static_cast<int>(nums.size())};
        int lo{0}, hi{n - 1}, mid;
        int min_value{nums[lo]};

        // Invariant: The search space [lo, hi] always contains the min value
        // unless we passed it already in which case we have already captured it.
        //
        // If the search space still contains the min, we go left or right based on
        // whether or not nums[mid] < nums[hi] or not.
        // If nums[mid] < nums[hi], it means either that the mid value is in the right section
        // so mid itself could be the min value which we will capture otherwise we go to the left
        // to find the drop point
        // Similarly if nums[mid] > nums[hi], it means that we are in the left section
        // and that we need to go right
        while (lo <= hi)
        {
            // Optimization: if nums[lo] < nums[hi], the range [lo, hi] is completely sorted
            // so we know that the minimum in remaining search space range is nums[lo]
            // and we can update the min based on nums[lo] and exit
            // Note: We could reach a monotonously increasing range even before coming across the
            // min value. Say mid index is the max value and then we go right, then the [lo, hi]
            // range will exactly capture the right section. We can check with the existing min
            // and return at this point. So it is important to compare the min with nums[lo].
            if (nums[lo] < nums[hi])
                return std::min(min_value, nums[lo]);

            // Find the mid value and update the candidate variable
            mid = lo + (hi - lo) / 2;
            min_value = std::min(min_value, nums[mid]);

            // If the mid value is less than the hi's value it means mid is in the
            // right section of the rotated array, which means we can go left and look
            // for a better solution
            // There need not be a better solution because mid itself might be the min
            // and going left will only have all values greater than the min value
            if (nums[mid] < nums[hi])
                hi = mid - 1;

            // Similarly if the mid value is greater than hi's value, it means that
            // mid is in the left section of the rotated area
            else
                lo = mid + 1;
        }

        return min_value;
    }
};