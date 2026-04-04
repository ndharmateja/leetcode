#include <vector>
#include <bitset>
#include <array>

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>> &board)
    {
        // Maps that keep track of which digits have occurred so far
        // for each row, each col and each square
        std::array<std::bitset<9>, 9> row_map;
        std::array<std::bitset<9>, 9> col_map;
        std::array<std::bitset<9>, 9> square_map;

        // Go over each digit in the sudoku and see if they already occurred
        // in any of the rows/cols/squares and if not we mark them as occurred
        for (int row = 0; row < 9; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {
                // If the char is '.' we can skip as it indicates an empty square
                unsigned char digit = board[row][col];
                if (digit == '.')
                    continue;

                // Convert the char digit into 0-based number
                // We are converting into 0-based instead of 1-based so that we could
                // use a bitset of 9 bits instead of 10 bits (as 0 digit doesn't
                // occur in sudoku)
                // Eg: '1' -> 0, '2' -> 1, ... , '8' -> 7, '9' -> 8
                digit = (digit - '0') - 1;

                // square_index: represents the index of the square (0-index)
                // Think of the 9x9 grid as a 3x3 grid of squares
                // row/3 tells us what row we are in the 3x3 grid of square
                // col/3 tells us what col we are in the 3x3 grid of square
                // For any 2d array, we can calculate the index considering the 2d array
                // as row majored 1d array using (r, c) -> (#cols * r) + c
                int square_index = 3 * (row / 3) + (col / 3);

                // Check if this digit is already present in any of the rows/cols/squares
                // that we have already seen
                // If this digit already occurred in any of the rows/cols/squares
                // then we can directly return false as it is not a valid sudoku
                if (row_map[row].test(digit) ||
                    col_map[col].test(digit) ||
                    square_map[square_index].test(digit))
                    return false;

                // If they didn't already occur, we mark them as occurred
                row_map[row].set(digit);
                col_map[col].set(digit);
                square_map[square_index].set(digit);
            }
        }

        return true;
    }
};