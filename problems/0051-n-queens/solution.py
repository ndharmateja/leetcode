from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        # Invariant: (row, col) is a valid position for a queen
        def dfs(row, col):
            # Place the queen at (row, col)
            col_positions[row] = col
            col_visited[col] = True
            main_diagonal_visited[row - col + n - 1] = True
            other_diagonal_visited[row + col] = True

            # If the row is n-1, it means that we have found a
            # valid placement of n-queens
            # so we can add the solution and exit
            if row == n-1:
                result_col_positions.append(col_positions[:])

            # Otherwise continue backtracking the next row
            else:
                new_r = row + 1
                for new_c in range(n):
                    if (not col_visited[new_c] 
                        and not main_diagonal_visited[new_r - new_c + n - 1]
                        and not other_diagonal_visited[new_r + new_c]):
                        dfs(new_r, new_c)

            # Remove the queen at (row, col)
            other_diagonal_visited[row + col] = False
            main_diagonal_visited[row - col + n - 1] = False
            col_visited[col] = False
            col_positions[row] = -1
    
        # col_visited, main_diagonal_visited, other_diagonal_visited keep track
        # of whether or not each col, main diagoanl and other diagonal is visited
        # r-c value goes from -(n-1) to (n-1) for each of the main diagonals
        # so (r-c)+(n-1) goes from 0 to (2n-1), so we can use (r-c)+(n-1) as an index
        # for each of the main diagonals
        # r+c value goes from 0 to (2n-1) for each of the other diagonals
        # so we can use r+c as an index for each of the other diagonals
        col_visited = [False for _ in range(n)]
        main_diagonal_visited = [False for _ in range(2*n - 1)]
        other_diagonal_visited = [False for _ in range(2*n - 1)]
        col_positions = [-1 for _ in range(n)]
        result_col_positions = []
        for i in range(n):
            dfs(0, i)

        # result_col_positions looks like [[1, 3, 0, 2], [2, 0, 3, 1]]
        # which means the solution is 
        # [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
        #
        # Optimization: instead of computing strings every time we can cache them
        # for n = 4, lookup list is
        # c = 0 => "Q..."
        # c = 1 => ".Q.."
        # c = 2 => "..Q."
        # c = 3 => "...Q"
        lookup = ["." * i + "Q" + "." * (n - 1 - i) for i in range(n)]
        return [[lookup[c] for c in board] for board in result_col_positions]