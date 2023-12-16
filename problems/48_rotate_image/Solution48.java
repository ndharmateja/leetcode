import java.util.Arrays;

class Solution48 {
    private void cyclicRotation(int[][] matrix, int r, int k, int n) {
        int x = matrix[r][r + k];
        matrix[r][r + k] = matrix[n - r - (k + 1)][r];
        matrix[n - r - (k + 1)][r] = matrix[n - r - 1][n - r - (k + 1)];
        matrix[n - r - 1][n - r - (k + 1)] = matrix[r + k][n - r - 1];
        matrix[r + k][n - r - 1] = x;
    }

    public void rotate(int[][] matrix) {
        int n = matrix.length;
        for (int r = 0; r <= n / 2; r++) {
            for (int k = 0; k < n - 2 * r - 1; k++) {
                cyclicRotation(matrix, r, k, n);
            }
        }
    }

    public static void main(String[] args) {
        int[][] matrix = new int[][] {
                { 5, 1, 9, 11 },
                { 2, 4, 8, 10 },
                { 13, 3, 6, 7 },
                { 15, 14, 12, 16 } };
        new Solution48().rotate(matrix);
        System.out.println(Arrays.deepToString(matrix));
    }
}