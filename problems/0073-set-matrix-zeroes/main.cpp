#include <vector>

class Solution
{
private:
    /**
     * Theta(mn) time and Theta(m + n) space solution
     * where m = #rows and n = #cols
     */
    static void solution1(std::vector<std::vector<int>> &matrix)
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

public:
    void setZeroes(std::vector<std::vector<int>> &matrix) { return solution1(matrix); }
};