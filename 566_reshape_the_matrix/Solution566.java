class Solution566 {
    public int[][] matrixReshape(int[][] mat, int rows, int cols) {
        if (rows * cols != mat.length * mat[0].length)
            return mat;
        int row = 0;
        int col = 0;
        int[][] out = new int[rows][cols];
        for (int i = 0; i < mat.length; i++) {
            for (int j = 0; j < mat[0].length; j++) {
                out[row][col++] = mat[i][j];
                if (col >= cols) {
                    row++;
                    col = 0;
                }
            }
        }
        return out;
    }

}