#include <vector>

class Solution
{
private:
    /**
     * TODO: add explanation
     */
    static void solution1(std::vector<std::vector<int>> &matrix)
    {
        /**
         * Consider a 6x6 matrix. The order of rotations happen as:
         * #  .  .  .  .  #    .  #  .  .  .  .    .  .  #  .  .  .    .  .  .  #  .  .    .  .  .  .  #  .
         * .  .  .  .  .  .    .  .  .  .  .  #    .  .  .  .  .  .    .  .  .  .  .  .    #  .  .  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  #    #  .  .  .  .  .    .  .  .  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    #  .  .  .  .  .    .  .  .  .  .  #    .  .  .  .  .  .
         * .  .  .  .  .  .    #  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  #
         * #  .  .  .  .  #    .  .  .  .  #  .    .  .  .  #  .  .    .  .  #  .  .  .    .  #  .  .  .  .
         *
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .
         * .  #  .  .  #  .    .  .  #  .  .  .    .  .  .  #  .  .
         * .  .  .  .  .  .    .  .  .  .  #  .    .  #  .  .  .  .
         * .  .  .  .  .  .    .  #  .  .  .  .    .  .  .  .  #  .
         * .  #  .  .  #  .    .  .  .  #  .  .    .  .  #  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .
         *
         * .  .  .  .  .  .
         * .  .  .  .  .  .
         * .  .  #  #  .  .
         * .  .  #  #  .  .
         * .  .  .  .  .  .
         * .  .  .  .  .  .
         */
        int n{static_cast<int>(matrix.size())};
        int half_n{n / 2};
        int r, k;
        int start, end, length;
        for (r = 0; r < half_n; r++)
        {
            end = n - r - 1;
            length = n - 2 * r;
            for (k = 0; k < length - 1; k++)
            {
                int temp = matrix[r][r + k];
                matrix[r][r + k] = matrix[end - k][r];
                matrix[end - k][r] = matrix[end][end - k];
                matrix[end][end - k] = matrix[r + k][end];
                matrix[r + k][end] = temp;
            }
        }
    }

public:
    void rotate(std::vector<std::vector<int>> &matrix) { solution1(matrix); }
};
