#include <iostream>
#include <vector>

class Solution
{
private:
    /**
     * Searches the 2D as a one big row major ordered 1D array
     * Does this iteratively but very easy to implement the recursive version of this
     * Theta(log(mn)) time and Theta(1) space in worst case
     * where m = #rows, n = #cols
     */
    static bool solution1(const std::vector<std::vector<int>> &matrix, int target)
    {
        // 1 <= num_rows, num_cols <= 100
        // so the following code won't throw any errors
        int num_rows{static_cast<int>(matrix.size())};
        int num_cols{static_cast<int>(matrix[0].size())};
        int lo{0}, hi{num_rows * num_cols - 1}, mid, r, c;
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            r = mid / num_cols;
            c = mid % num_cols;
            if (target < matrix[r][c])
                hi = mid - 1;
            else if (target > matrix[r][c])
                lo = mid + 1;
            else
                return true;
        }

        // If we reach here it means that we haven't found the target
        return false;
    }

    /**
     * Dual binary search solution
     * First binary search using candidate variable pattern to find the row
     * and then the regular binary search to find the target in the
     * specified row
     *
     * Theta(log m + log n) time and Theta(1) space in the worst case
     * where m = #rows, n = #cols
     */
    static bool solution2(const std::vector<std::vector<int>> &matrix, int target)
    {
        // First look for the row in which the target could be
        // We need to look for the rightmost row whose first value <= target
        int num_rows{static_cast<int>(matrix.size())};
        int num_cols{static_cast<int>(matrix[0].size())};
        int lo{0}, hi{num_rows - 1}, mid, target_row_index{-1};
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            if (target < matrix[mid][0])
            {
                // We need to go to the left
                hi = mid - 1;
            }

            // if (target >= matrix[mid][0])
            // We found a potential better answer, but we could do better so
            // we search in the right half
            else
            {
                target_row_index = mid;
                lo = mid + 1;
            }
        }

        // At this point if answer was -1, the target is not in the matrix
        if (target_row_index == -1)
            return false;

        // Look for the target in the matrix[answer] row
        // Regular binary search
        lo = 0, hi = num_cols - 1;
        while (lo <= hi)
        {
            mid = lo + (hi - lo) / 2;
            if (target < matrix[target_row_index][mid])
                hi = mid - 1;
            else if (target > matrix[target_row_index][mid])
                lo = mid + 1;
            else
                return true;
        }

        // If we reach here, the target is not present in the row
        return false;
    }

public:
    bool searchMatrix(const std::vector<std::vector<int>> &matrix, int target) { return solution2(matrix, target); }
};