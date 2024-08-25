class Solution867 {
    public int[][] transpose(int[][] matrix) {
        int rows = matrix.length;
        int columns = matrix[0].length;
        int[][] output = new int[columns][rows];
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                output[i][j] = matrix[j][i];
            }
        }
        return output;
    }
}