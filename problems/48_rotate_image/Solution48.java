public class Solution48 {
    /**
     * Eg:
     * For r = 0, k = 1 the elements in # will be cyclically
     * exchanged clockwise
     * # . . . #
     * . . . . .
     * . . . . .
     * . . . . .
     * # . . . #
     * 
     * For r = 0, k = 1 the elements in # will be cyclically
     * exchanged clockwise
     * . # . . .
     * . . . . #
     * . . . . .
     * # . . . .
     * . . . # .
     * 
     * For r = 0, k = 2 the elements in # will be cyclically
     * exchanged clockwise
     * . . # . .
     * . . . . .
     * # . . . #
     * . . . . .
     * . . # . .
     * 
     * For r = 0, k = 3 the elements in # will be cyclically
     * exchanged clockwise
     * . . . # .
     * # . . . .
     * . . . . .
     * . . . . #
     * . # . . .
     * 
     * For r = 1, k = 0 the elements in # will be cyclically
     * exchanged clockwise
     * . . . . .
     * . # . # .
     * . . . . .
     * . # . # .
     * . . . . .
     * 
     * For r = 1, k = 1 the elements in # will be cyclically
     * exchanged clockwise
     * . . . . .
     * . . # . .
     * . # . # .
     * . . # . .
     * . . . . .
     * 
     * @param matrix
     * @param r
     * @param k
     * @param n
     */
    private void oneCyclicRotation(int[][] matrix, int r, int k, int n) {
        int x = matrix[r][r + k];
        matrix[r][r + k] = matrix[n - r - (k + 1)][r];
        matrix[n - r - (k + 1)][r] = matrix[n - r - 1][n - r - (k + 1)];
        matrix[n - r - 1][n - r - (k + 1)] = matrix[r + k][n - r - 1];
        matrix[r + k][n - r - 1] = x;
    }

    /**
     * O(n*n) time and O(1) space complexity
     * 
     * @param matrix
     */
    public void rotate(int[][] matrix) {
        int n = matrix.length;
        for (int r = 0; r <= n / 2; r++) {
            for (int k = 0; k < n - 2 * r - 1; k++) {
                oneCyclicRotation(matrix, r, k, n);
            }
        }
    }
}