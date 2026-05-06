#include <vector>

class Solution
{
private:
    /**
     * Recursive function that adds the values in spiral order
     */
    static void solution1(const std::vector<std::vector<int>> &matrix,
                          std::vector<int> &result,
                          int start_r, int end_r, int start_c, int end_c)
    {
        // Base case
        if (start_r > end_r || start_c > end_c)
            return;

        // Easy cases
        // If there is exactly one row or column we can add them to the result and exit
        // Only one row
        int r, c;
        if (start_r == end_r)
        {
            for (c = start_c; c <= end_c; c++)
                result.push_back(matrix[start_r][c]);
            return;
        }

        // Only one col
        if (start_c == end_c)
        {
            for (r = start_r; r <= end_r; r++)
                result.push_back(matrix[r][start_c]);
            return;
        }

        // Atleast 2 rows and 2 cols
        // We can do one spiral around the matrix and add the elements and call
        // this function recursively on the inner square
        // Add the first row
        for (c = start_c; c <= end_c; c++)
            result.push_back(matrix[start_r][c]);
        // Add the last column values (except for the ones in the first and last rows)
        for (r = start_r + 1; r <= end_r - 1; r++)
            result.push_back(matrix[r][end_c]);
        // Add the last row in reverse
        for (c = end_c; c >= start_c; c--)
            result.push_back(matrix[end_r][c]);
        // Add the first column values in reverse (except for the ones in the first and last rows)
        for (r = end_r - 1; r >= start_r + 1; r--)
            result.push_back(matrix[r][start_c]);

        // Recursively call this on the inner square
        // This can also take advantage of tail recursion
        solution1(matrix, result, start_r + 1, end_r - 1, start_c + 1, end_c - 1);
    }

    /**
     * Wrapper function for the recursive function.
     *
     * Theta(mn) time and Theta(min{m, n}) space (for recursion) solution
     * Theta(1) space if tail recursion occurs
     * where m = #rows and n = #cols
     */
    static std::vector<int> solution1(const std::vector<std::vector<int>> &matrix)
    {
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        std::vector<int> result;
        result.reserve(m * n);
        solution1(matrix, result, 0, m - 1, 0, n - 1);
        return result;
    }

    /**
     * Iterative version of solution1
     * Theta(mn) time and Theta(1) space solution
     * where m = #rows and n = #cols
     */
    static std::vector<int> solution2(const std::vector<std::vector<int>> &matrix)
    {
        // Init the result and boundary variables
        // Reserve the space in the vector so that we can prevent multiple resizes
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        int start_r{0}, end_r{m - 1}, start_c{0}, end_c{n - 1};
        std::vector<int> result;
        result.reserve(m * n);

        // Keep adding the elements in the spiral order as long as there are atleast
        // 2 rows and 2 cols left
        int r, c;
        while (start_r < end_r && start_c < end_c)
        {
            // Add the first row
            for (c = start_c; c <= end_c; c++)
                result.push_back(matrix[start_r][c]);
            // Add the last column values (except for the ones in the first and last rows)
            for (r = start_r + 1; r <= end_r - 1; r++)
                result.push_back(matrix[r][end_c]);
            // Add the last row in reverse
            for (c = end_c; c >= start_c; c--)
                result.push_back(matrix[end_r][c]);
            // Add the first column values in reverse (except for the ones in the first and last rows)
            for (r = end_r - 1; r >= start_r + 1; r--)
                result.push_back(matrix[r][start_c]);

            // Update the boundaries
            start_r++;
            end_r--;
            start_c++;
            end_c--;
        }

        // If just one row or one column left add its elements
        // We need the "else if" and not just "if" for the start_c==end_c
        // as we could be left with exactly one cell in which case it will be added two times
        if (start_r == end_r)
            for (c = start_c; c <= end_c; c++)
                result.push_back(matrix[start_r][c]);
        else if (start_c == end_c)
            for (r = start_r; r <= end_r; r++)
                result.push_back(matrix[r][start_c]);

        // Return the result
        return result;
    }

public:
    std::vector<int> spiralOrder(const std::vector<std::vector<int>> &matrix) { return solution2(matrix); }
};
