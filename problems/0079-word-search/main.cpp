#include <vector>
#include <string>

class Solution
{

private:
    static constexpr int drs[] = {-1, 1, 0, 0};
    static constexpr int dcs[] = {0, 0, -1, 1};

    /**
     * Invariants:
     * 1. (r, c) is a valid cell on the board
     * 2. (r, c) is unvisited (and will remain unvisited even after the dfs call)
     * 3. The word[:buffer_len] is already found on the board with the board[r][c] being
     *   the last of the prefix => word[buffer_len - 1] is the same as board[r][c]
     *    a. Think of board[r][c] is the last char of an imaginary buffer = word[:buffer_len]
     *    b. We don't need to explicitly maintain a buffer as word[:buffer_len]
     *      represents the buffer anyway.
     *
     * For more details, see the 2 solutions of word search 2 problem (lc 212)
     * for the lookahead vs basecase approaches of recursion
     */
    static bool dfs(std::vector<std::vector<char>> &board, int buffer_len,
                    int r, int c, int m, int n, const std::string &word)
    {
        // If the length of the buffer matches the word's length
        // it means we have found the given word as the buffer is a valid prefix
        // of the given word
        if (buffer_len == word.size())
            return true;

        // Mark this cell as visited so that we don't use this cell as part of further words
        // in the recursive dfs calls
        // Store the original character before marking it as visited so that we can restore it
        unsigned char ch = board[r][c];
        board[r][c] = '#';

        // Visit all the unvisited neighbours of the current cell that contains the next
        // character in the given string
        // To maintain the invariant, we only call dfs on cells that are unvisited and within
        // the board's boundaries and such that the next cell's character is the next valid
        // character in the given word so that buffer still remains a prefix
        int r_n, c_n;
        unsigned char ch_n;
        for (int i = 0; i < 4; i++)
        {
            // If the (r_n, c_n) is out of bounds, we don't need to explore the neighbour
            r_n = r + drs[i];
            c_n = c + dcs[i];
            if (r_n < 0 || r_n >= m || c_n < 0 || c_n >= n)
                continue;

            // If the neighbouring cell is already visited, we can skip exploring it
            ch_n = board[r_n][c_n];
            if (ch_n == '#')
                continue;

            // buffer + the new char should also be a valid prefix of the word (given that
            // buffer is a valid prefix of the word)
            // It means that word[:buffer_len + 1] should be the prefix with board[r_n][c_n]
            // being its last character
            // So we essentially need to check if word[buffer_len] is the same as the next char
            // If it is not we don't have to explore it
            if (word[buffer_len] != ch_n)
                continue;

            // Add the next character to the buffer and explore the unvisited neighbour
            // If the dfs call returns true, it means that we found the word in this particular
            // neighbour
            // So we can immediately exit without having to visit other neighbours
            if (dfs(board, buffer_len + 1, r_n, c_n, m, n, word))
                return true;
        }

        // Unmark this cell as visited because we are backtracking and we are done with the dfs call
        // on the current cell
        board[r][c] = ch;

        // If we reached here it means that this cell is not the end of the word
        // and none of the neighbours returned true. So we return false.
        return false;
    }

    static bool sol1(std::vector<std::vector<char>> &board, const std::string &word)
    {
        /**
         * Improvements:
         * 1. Just maintain the buffer length instead of the actual buffer as the buffer
         *   is anyways the prefix of the word. (~60% -to ~95% improvement on leetcode)
         * 2. No explicit visited 2d vector. We just '#' char on the board to mark it visited.
         */

        // Run DFS starting from each of the cells see if the word exists using backtracking
        // We only start backtracking from cells that have the first char of the word
        // otherwise we know that we can't form the given word starting from this cell
        int m{static_cast<int>(board.size())}, n{static_cast<int>(board[0].size())};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                // If a dfs call returns true, it means that we have found the word starting
                // from that cell, so we can immediately return true
                if (word[0] == board[r][c] && dfs(board, 1, r, c, m, n, word))
                    return true;

        // Return the result
        return false;
    }

public:
    bool exist(std::vector<std::vector<char>> &board, const std::string &word) { return sol1(board, word); }
};