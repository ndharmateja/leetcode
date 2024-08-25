import java.util.HashSet;
import java.util.Set;

class Solution2133 {
    public boolean checkValid(int[][] matrix) {
        Set<Integer> set = new HashSet<>();
        int n = matrix.length;
        for (int row = 0; row < n; row++) {
            set.clear();
            for (int i = 0; i < n; i++) {
                if (matrix[row][i] == '.')
                    continue;
                int value = matrix[row][i];
                if (set.contains(value) || value < 1 || value > n) {
                    return false;
                } else {
                    set.add(value);
                }
            }
        }

        for (int col = 0; col < n; col++) {
            set.clear();
            for (int i = 0; i < n; i++) {
                if (matrix[i][col] == '.')
                    continue;
                int value = matrix[i][col];
                if (set.contains(value) || value < 1 || value > n) {
                    return false;
                } else {
                    set.add(value);
                }
            }
        }

        return true;
    }
}