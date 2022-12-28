class Solution1929 {

    private int[][] rotateClockwise(int[][] arr) {
        int n = arr.length;
        int[][] out = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                out[i][j] = arr[n - j - 1][i];
            }
        }
        return out;
    }

    private boolean areArraysEqual(int[][] arr1, int[][] arr2) {
        int n = arr1.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr1[i][j] != arr2[i][j])
                    return false;
            }
        }
        return true;
    }

    public boolean findRotation(int[][] mat, int[][] target) {
        if (areArraysEqual(mat, target))
            return true;

        int[][] temp = mat;
        for (int i = 0; i < 3; i++) {
            temp = rotateClockwise(temp);
            if (areArraysEqual(temp, target))
                return true;
        }

        return false;
    }
}