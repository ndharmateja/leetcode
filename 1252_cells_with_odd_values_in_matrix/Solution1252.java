import java.util.Arrays;

class Solution1252 {
    public int oddCells(int m, int n, int[][] indices) {
        int[][] matrix = new int[m][n];
        for (int[] index : indices) {
            int row = index[0];
            int col = index[1];
            for (int j = 0; j < n; j++) {
                matrix[row][j] += 1;
            }
            for (int i = 0; i < m; i++) {
                matrix[i][col] += 1;
            }
        }
        return Arrays
                .stream(matrix)
                .mapToInt(row -> Arrays
                        .stream(row)
                        .filter(num -> num % 2 != 0)
                        .map(e -> 1)
                        .sum())
                .sum();

    }
}