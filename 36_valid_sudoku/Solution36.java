import java.util.HashSet;
import java.util.Set;

public class Solution36 {
    public boolean isValidSudoku(char[][] board) {
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

        set.clear();
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

}
