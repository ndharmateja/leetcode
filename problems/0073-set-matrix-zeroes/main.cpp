#include <vector>

class Solution
{
private:
    /**
     * Theta(mn) time and Theta(m + n) space solution
     * where m = #rows and n = #cols
     */
    static void sol1(std::vector<std::vector<int>> &matrix)
    {
        // Use one vector of bools each for the rows and one for the cols
        // to keep track of which rows and cols have 0s in them
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<bool> row_flags(m), col_flags(n);
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (!matrix[r][c])
                {
                    row_flags[r] = true;
                    col_flags[c] = true;
                }

        // Make all the cells 0 that either have the row flags or col flags set at that index
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (row_flags[r] || col_flags[c])
                    matrix[r][c] = 0;
    }

    /**
     * Theta(mn) time and Theta(1) space solution
     * Uses the first row and the first column as flags instead of separate vectors
     * where m = #rows and n = #cols
     */
    static void sol2(std::vector<std::vector<int>> &matrix)
    {
        // We use the first row of the matrix to keep track of which cols have zeroes
        // in them instead of in separate vectors
        // Similarly we use the first column to keep track of which rows have zeroes
        // Because, there would be interactions between the first row and the first col
        // we are going to handle them separately
        // ! Note: We make the value in matrix[0][c] as 0 if there is a zero in the col 'c'
        // We only store the flags in the first row for columns [1, n]
        // We only store the flags in the first col for rows [1, m]

        // Check if the first row and the column need to be zeroed before
        // using them as flags
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        bool first_row_has_zero{false}, first_col_has_zero{false};
        for (int c = 0; c < n; c++)
            if (!matrix[0][c])
            {
                first_row_has_zero = true;
                break;
            }
        for (int r = 0; r < m; r++)
            if (!matrix[r][0])
            {
                first_col_has_zero = true;
                break;
            }

        // Update the zeroes information in the first row and first column
        // based on rows [1, m] and cols [1, n]
        for (int r = 1; r < m; r++)
            for (int c = 1; c < n; c++)
                if (!matrix[r][c])
                {
                    matrix[r][0] = 0;
                    matrix[0][c] = 0;
                }

        // Make all the cells 0 that either have the row flags or col flags set at that index
        for (int r = 1; r < m; r++)
            for (int c = 1; c < n; c++)
                if (!matrix[r][0] || !matrix[0][c])
                    matrix[r][c] = 0;

        // Make the first row or col zero appropriately
        if (first_row_has_zero)
            for (int c = 0; c < n; c++)
                matrix[0][c] = 0;
        if (first_col_has_zero)
            for (int r = 0; r < m; r++)
                matrix[r][0] = 0;
    }

public:
    void setZeroes(std::vector<std::vector<int>> &matrix) { return sol2(matrix); }
};