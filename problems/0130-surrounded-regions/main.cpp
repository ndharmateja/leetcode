#include <vector>
#include <queue>
#include <utility>

class Solution
{
private:
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Theta(mn) time and O(V) space
     * where m = #rows, n = #cols, V = #verices
     * See problem 417 for more details. Using a very similar idea.
     */
    static void solution1(std::vector<std::vector<char>> &board)
    {
        // If there are 2 or less rows or 2 or less cols, then there won't be any surrounded regions
        int num_rows{static_cast<int>(board.size())}, num_cols{static_cast<int>(board[0].size())};
        if (num_rows <= 2 || num_cols <= 2)
            return;

        // Run BFS from all the graph nodes on the edges and mark them with '-'
        // to indicate all the islands that aren't surrounded
        std::queue<std::pair<int, int>> queue;

        // Add all the graph nodes on the edges to the queue as the source nodes
        // Add the first and last cols
        for (int r = 0; r < num_rows; r++)
        {
            if (board[r][0] == 'O')
            {
                queue.push({r, 0});
                board[r][0] = '-';
            }
            if (board[r][num_cols - 1] == 'O')
            {
                queue.push({r, num_cols - 1});
                board[r][num_cols - 1] = '-';
            }
        }
        // Add the first and last rows (except cells in the first and last cols
        // as we already added them above)
        for (int c = 1; c < num_cols - 1; c++)
        {
            if (board[0][c] == 'O')
            {
                queue.push({0, c});
                board[0][c] = '-';
            }
            if (board[num_rows - 1][c] == 'O')
            {
                queue.push({num_rows - 1, c});
                board[num_rows - 1][c] = '-';
            }
        }

        // Run BFS from all the source nodes to mark all the non-surrounded regions with '-'
        while (!queue.empty())
        {
            // Pop the next element and add its neighbours
            auto [r, c] = queue.front();
            queue.pop();

            // Add each unvisited neighbour (only a neighbour if cell has 'O')
            // And it is visited if cell has '-'
            // so we only need to check if cell has 'O' to check if it is an unvisited neighbour
            for (auto [dr, dc] : directions)
            {
                int new_r = r + dr;
                int new_c = c + dc;
                if ((0 <= new_r && new_r < num_rows) &&
                    (0 <= new_c && new_c < num_cols) &&
                    board[new_r][new_c] == 'O')
                {
                    queue.push({new_r, new_c});
                    board[new_r][new_c] = '-';
                }
            }
        }

        // At this point all the non-surrounded regions have '-'
        // and the surrounded regions have 'O'
        // So we can mark them accordingly for the result
        for (int r = 0; r < num_rows; r++)
            for (int c = 0; c < num_cols; c++)
            {
                // If cell is part of surrounded region, make it X
                // If cell is part of non-surrounded region, make it O
                // if (board[r][c] == 'O')
                //     board[r][c] = 'X';
                // else if (board[r][c] == '-')
                //     board[r][c] = 'O';
                board[r][c] = board[r][c] == 'O'
                                  ? 'X'
                                  : (board[r][c] == '-' ? 'O' : board[r][c]);
            }
    }

public:
    void solve(std::vector<std::vector<char>> &board) { solution1(board); }
};