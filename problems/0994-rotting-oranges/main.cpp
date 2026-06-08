#include <vector>
#include <queue>
#include <utility>

class Solution
{
private:
    inline static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Multi source BFS solution
     * Theta(mn) time and O(V) space
     * where m = #rows, n = #cols, V = #vertices
     *
     * See problem 417 for more details. Using a very similar idea.
     */
    static int solution1(std::vector<std::vector<int>> &board)
    {
        // Run BFS starting with the source nodes as all the rotten oranges
        // When each layer of BFS runs, we can increment the count of num_minutes by 1
        int num_rows{static_cast<int>(board.size())}, num_cols{static_cast<int>(board[0].size())};
        std::queue<std::pair<int, int>> queue;

        // Add all the rotten oranges to the queue
        // Since they are already rotten (=2) which we are using to not visit
        // again, we don't have to explicitly make the cells as 2
        int num_fresh_oranges{0};
        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                if (board[r][c] == 2)
                    queue.push({r, c});
                else if (board[r][c] == 1)
                    num_fresh_oranges++;
            }
        }

        // Optimization: If number of fresh oranges is 0, then the answer is 0
        // as no fresh oranges for us to rot
        if (num_fresh_oranges == 0)
            return 0;

        // Run BFS from all the source nodes
        int num_minutes{0};
        while (!queue.empty())
        {
            // At this point, the queue has only the nodes from one layer
            // So we pop all the nodes and add their children to form the next layer
            int num_elements_in_layer{static_cast<int>(queue.size())};

            // For each element in the queue, we pop it and add its unvisited neighbours to the queue
            for (int i = 0; i < num_elements_in_layer; i++)
            {
                // Pop the next element and add its neighbours
                auto [r, c] = queue.front();
                queue.pop();

                // Add each unvisited neighbour (only a neighbour if it is a fresh orange (1))
                // And it is visited if cell has 2 (rotten orange)
                // so we only need to check if cell has 1 to check if it is an unvisited neighbour
                // ! Mark a cell visited as soon as we discover it to avoid adding same cells
                // ! multiple times to the queue
                for (auto [dr, dc] : directions)
                {
                    int new_r = r + dr;
                    int new_c = c + dc;
                    if ((0 <= new_r && new_r < num_rows) &&
                        (0 <= new_c && new_c < num_cols) &&
                        board[new_r][new_c] == 1)
                    {
                        // Make the fresh orange rotten and add it to the queue
                        board[new_r][new_c] = 2;
                        num_fresh_oranges--;
                        queue.push({new_r, new_c});
                    }
                }
            }

            // One minute has passed as one layer was processed
            num_minutes++;
        }

        // At this point all the rotten oranges have successfully spoiled all the
        // fresh oranges they could reach
        // If any of the oranges is still fresh, it means that the fresh orange
        // wasn't reachable, so we can return -1
        // for (int r = 0; r < num_rows; r++)
        //     for (int c = 0; c < num_cols; c++)
        //         if (board[r][c] == 1)
        //             return -1;

        // To prevent the above nested loop, we could count the number of fresh oranges initially
        // and decrement it everytime we rot one fresh orange
        if (num_fresh_oranges > 0)
            return -1;

        // If we reach this point, it means that there was atleast one fresh orange
        // and the rotten oranges were able to rot all the fresh oranges
        // The case where there were no rotten oranges would have been handled above
        // in the num_fresh_oranges > 0 check (as the number of fresh oranges would be greater than 0
        // if there were no rotten oranges to begin with)
        // So we conclude that there was atleast fresh orange and the rotten oranges were able to rot
        // all of the fresh oranges
        // So num_minutes is not going to be 0 at this point
        // The num_minutes at this point will be the number of "layers" of rotten oranges
        // and since we need to return the number of minutes, we need to subtract 1
        // as we don't need to account for rotting the first layer
        return num_minutes - 1;
    }

public:
    int orangesRotting(std::vector<std::vector<int>> &board) { return solution1(board); }
};