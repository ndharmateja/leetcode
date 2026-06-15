from typing import List

class Solution:
    @staticmethod
    def sol1(n: int) -> List[List[str]]:
        # Invariants: 
        # 1. (row, col) is a valid position for a queen
        # 2. col_visited[c] = True for all the column positions of the queens
        #   in the rows 0 to row-1
        def dfs(row, col):
            # Place the queen at (row, col)
            col_positions[row] = col
            col_visited[col] = True
            main_diagonal_visited[row - col + n - 1] = True
            anti_diagonal_visited[row + col] = True

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
                        and not anti_diagonal_visited[new_r + new_c]):
                        dfs(new_r, new_c)

            # Remove the queen at (row, col)
            anti_diagonal_visited[row + col] = False
            main_diagonal_visited[row - col + n - 1] = False
            col_visited[col] = False
            col_positions[row] = -1
    
        # Lists col_visited, main_diagonal_visited, other_diagonal_visited keep track
        # of whether or not each col, main diagoanl and anti diagonal is visited
        # For each of the main diagonals, r-c value goes from -(n-1) to (n-1)
        # so (r-c)+(n-1) goes from 0 to (2n-1), so we can use (r-c)+(n-1) as an index
        # for each of the main diagonals
        # For each of the anti diagonals, r+c value goes from 0 to (2n-1)
        # so we can use r+c as an index for each of the anti diagonals
        col_visited = [False for _ in range(n)]
        main_diagonal_visited = [False for _ in range(2*n - 1)]
        anti_diagonal_visited = [False for _ in range(2*n - 1)]
        col_positions = [-1 for _ in range(n)]
        result_col_positions = []
        for i in range(n):
            dfs(0, i)

        # If result_col_positions looks like [[1, 3, 0, 2], [2, 0, 3, 1]]
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
    
    # Logic exactly same as solution 1, except we use bit patterns to track
    # dangerous cols and diagonals
    @staticmethod
    def sol2(n: int) -> List[List[str]]:
        # Invariants: 
        # 1. (r, c) is a valid position (not vulnerable to attack from any of the placed queens so far) 
        #   for a queen
        # 2. the bit pattern of col_visited keeps track of visited columns in rows 0 to r-1
        #   in reverse order. Eg: 0b00001001 means that queens were in columsn 0 and 3
        # 3. the bit pattern of main_diagonal_visited keeps track of the vulnerable columns
        #   in row 'r' from queens along main diagonals (in reverse order)
        #   Eg: 0b00011101 means that queens can attack along the main diagonal in the column
        #   positions 0, 2, 3, 4 on row 'r'
        # 4. very similarly anti_diagonal_visited
        def dfs(r, c, col_visited, main_diagonal_visited, anti_diagonal_visited):
            # Place the queen at (r, c)
            # Mark the column visited in the col_visited bit pattern
            # Now that we have placed a queen in column 'c' on row 'r', that position is 
            # vulnerable for diagonal attacks (both main and anti)
            col_positions[r] = c
            col_visited |= (1 << c)
            main_diagonal_visited |= (1 << c)
            anti_diagonal_visited |= (1 << c)

            # If the r is n-1, it means that we have found a
            # valid placement of n-queens
            # so we can add the solution and exit
            if r == n-1:
                result_col_positions.append(col_positions[:])

            # Otherwise continue backtracking the next row 'r+1'
            # The blocked positions for the next row are all the columns placed upto row 'r'
            # and the main diagonal vulnerability column positions for row 'r+1'
            # will be the same positions shifted one step to the right (but since we are storing
            # them in reverse order, we shift them to the left)
            # So the blocked positions for row 'r+1' is a bitwise OR of all the three
            # We backtrack along all the not blocked positions to hold the invariants
            else:
                blocked_positions = col_visited | (main_diagonal_visited << 1) | (anti_diagonal_visited >> 1)
                for new_c in range(n):
                    if not (blocked_positions & (1 << new_c)):
                        dfs(r + 1, new_c, col_visited, main_diagonal_visited << 1, anti_diagonal_visited >> 1)

            # Remove the queen at (r, c)
            # Not necessary to undo the bit patterns as these are local variables
            # anti_diagonal_visited ^= (1 << c)
            # main_diagonal_visited ^= (1 << c)
            # col_visited ^= (1 << c)
            col_positions[r] = -1
    
        # Lists col_visited, main_diagonal_visited, other_diagonal_visited keep track
        # of whether or not each col, main diagoanl and anti diagonal is visited
        # For each of the main diagonals, r-c value goes from -(n-1) to (n-1)
        # so (r-c)+(n-1) goes from 0 to (2n-1), so we can use (r-c)+(n-1) as an index
        # for each of the main diagonals
        # For each of the anti diagonals, r+c value goes from 0 to (2n-1)
        # so we can use r+c as an index for each of the anti diagonals
        col_positions = [-1 for _ in range(n)]
        result_col_positions = []
        for i in range(n):
            dfs(0, i, 0, 0, 0)

        # If result_col_positions looks like [[1, 3, 0, 2], [2, 0, 3, 1]]
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
    
    def solveNQueens(self, n: int) -> List[List[str]]:
        return Solution.sol2(n)