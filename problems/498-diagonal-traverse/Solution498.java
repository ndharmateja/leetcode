class Solution498 {
    public int[] findDiagonalOrder(int[][] mat) {
        int numRows = mat.length;
        int numCols = mat[0].length;
        int[] output = new int[numRows * numCols];
        int curr = 0;
        boolean inReverse = false;

        // sum goes from 0 to (rows + cols - 2)
        // For each sum (corresponding to one diagonal)
        // find the start and end values for row and col
        // And iterate over them to print
        for (int sum = 0; sum <= (numRows + numCols - 2); sum++) {
            // we use min for the case when sum crosses numRows
            int startRow = Math.min(sum, numRows - 1);

            // We use max for the case row=2,col=1 in a 3x3 matrix
            int startCol = Math.max(sum - startRow, 0);
            int endCol = Math.min(sum, numCols - 1);

            // Iterate in reverse or normal based on boolean
            if (!inReverse) {
                for (int col = startCol; col <= endCol; col++) {
                    int row = sum - col;
                    output[curr++] = mat[row][col];
                }
            } else {
                for (int col = endCol; col >= startCol; col--) {
                    int row = sum - col;
                    output[curr++] = mat[row][col];
                }
            }
            inReverse = !inReverse;
        }

        return output;
    }
}