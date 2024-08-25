import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Solution36 {
    // O(3n^2) time and O(n) space (n is 9)
    public boolean solution1(char[][] board) {
        Set<Integer> set = new HashSet<>();
        for (int row = 0; row < 9; row++) {
            set.clear();
            for (int i = 0; i < 9; i++) {
                if (board[row][i] == '.')
                    continue;
                int value = board[row][i] - '0';
                if (set.contains(value) || value < 1 || value > 9) {
                    return false;
                } else {
                    set.add(value);
                }
            }
        }

        for (int col = 0; col < 9; col++) {
            set.clear();
            for (int i = 0; i < 9; i++) {
                if (board[i][col] == '.')
                    continue;
                int value = board[i][col] - '0';
                if (set.contains(value) || value < 1 || value > 9) {
                    return false;
                } else {
                    set.add(value);
                }
            }
        }

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                set.clear();
                int rowStart = row * 3;
                int colStart = col * 3;
                for (int i = rowStart; i < rowStart + 3; i++) {
                    for (int j = colStart; j < colStart + 3; j++) {
                        if (board[i][j] == '.')
                            continue;
                        int value = board[i][j] - '0';
                        if (set.contains(value) || value < 1 || value > 9) {
                            return false;
                        } else {
                            set.add(value);
                        }
                    }
                }
            }
        }

        return true;
    }

    // O(n^2) time and O(3 * n * n) space
    public boolean solution2(char[][] board) {
        // three hash maps for rows, columns and squares
        // to check duplicates
        Map<Integer, Set<Character>> rowMap = new HashMap<>();
        Map<Integer, Set<Character>> colMap = new HashMap<>();
        Map<Integer, Set<Character>> squareMap = new HashMap<>();
        for (int i = 0; i < 9; i++) {
            rowMap.put(i, new HashSet<>());
            colMap.put(i, new HashSet<>());
            squareMap.put(i, new HashSet<>());
        }

        // iterate through all elements and see if it exists in the corresponding sets
        // of the three maps
        // if not add them
        for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board.length; c++) {
                char element = board[r][c];
                if (element == '.')
                    continue;

                int squareId = (r / 3) * 3 + (c / 3);
                if (!rowMap.get(r).add(element) || !colMap.get(c).add(element)
                        || !squareMap.get(squareId).add(element))
                    return false;
            }
        }

        // valid sudoku
        return true;
    }

    public boolean isValidSudoku(char[][] board) {
        return solution2(board);
    }
}
