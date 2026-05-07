#include <vector>

class Solution
{
private:
    static void solution1(std::vector<std::vector<int>> &matrix)
    {
        /**
         * Consider a 6x6 matrix. The order of rotations happen as:
         * r = 0; end = 5; length = 6
         * k = 0               k = 1               k = 2               k = 3               k = 4
         * #  .  .  .  .  #    .  #  .  .  .  .    .  .  #  .  .  .    .  .  .  #  .  .    .  .  .  .  #  .
         * .  .  .  .  .  .    .  .  .  .  .  #    .  .  .  .  .  .    .  .  .  .  .  .    #  .  .  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  #    #  .  .  .  .  .    .  .  .  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    #  .  .  .  .  .    .  .  .  .  .  #    .  .  .  .  .  .
         * .  .  .  .  .  .    #  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  #
         * #  .  .  .  .  #    .  .  .  .  #  .    .  .  .  #  .  .    .  .  #  .  .  .    .  #  .  .  .  .
         *
         * r = 1; end = 4; length = 4
         * k = 0               k = 1               k = 2
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .
         * .  #  .  .  #  .    .  .  #  .  .  .    .  .  .  #  .  .
         * .  .  .  .  .  .    .  .  .  .  #  .    .  #  .  .  .  .
         * .  .  .  .  .  .    .  #  .  .  .  .    .  .  .  .  #  .
         * .  #  .  .  #  .    .  .  .  #  .  .    .  .  #  .  .  .
         * .  .  .  .  .  .    .  .  .  .  .  .    .  .  .  .  .  .
         *
         * r = 2; end = 3; length = 2
         * k = 0
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

    /**
     * Flip the matrix vertically and then transpose it to rotate it clockwise
     */
    static void solution2(std::vector<std::vector<int>> &matrix)
    {
        /**
         * Explanation:
         * Say the matrix is
         * A  B  C  D     flip      M  N  O  P              M  I  E  A
         * E  F  G  H  vertically   I  J  K  L  transpose   N  J  F  B
         * I  J  K  L  ---------->  E  F  G  H  --------->  O  K  G  C
         * M  N  O  P               A  B  C  D              P  L  H  D
         *
         * Proof: Consider the square with the corner (r, r)
         * The vertices of this square will be:
         * top left    : (r, r)
         * top right   : (r, r + n - 1)
         * bottom left : (r + n - 1, r)
         * bottom right: (r + n - 1, r + n - 1)
         * and an element with offset k from the start in the first row of the square
         * the coordinates will be (r, r + k)
         * when flipped vertically this element goes to (r + n - 1, r + k)
         * and when transposed this element goes to (r + k, r + n - 1)
         * which is exactly the place (r, r + k) needs to go when the whole matrix
         * is rotated clockwise
         *
         * Similarly, flipping horizontally and transposing will rotate the matrix counterclockwise
         * transposing and flipping vertically will rotate the matrix counterclockwise
         * transposing and flipping horizontally will rotate the matrix clockwise
         *
         * But flipping the vector<vector<int>> vertically is Theta(n) operation as we just need to
         * swap the pointerss in the vector of vectors
         * So to rotate the matrix clockwise we flip the matrix vertically and then transpose it
         * and to rotate the matrix counterclockwise we transpose the matrix and then flip it vertically
         */

        // Flip the matrix vertically by reversing the vector of vectors
        // Theta(n) operation
        std::reverse(matrix.begin(), matrix.end());
        int n{static_cast<int>(matrix.size())};

        // Transpose the matrix
        int r, c;
        for (r = 0; r < n - 1; r++)
            for (c = r + 1; c < n; c++)
                std::swap(matrix[r][c], matrix[c][r]);
    }

public:
    void rotate(std::vector<std::vector<int>> &matrix) { solution2(matrix); }
};
