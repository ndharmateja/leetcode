import java.security.InvalidAlgorithmParameterException;
import java.util.ArrayList;
import java.util.List;

public class Solution54 {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> output = new ArrayList<>();

        int m = matrix.length;
        int n = matrix[0].length;

        // Add each row/col in appropriate direction
        // as long as they are in limits
        // Keep changing the limits accordingly after each addition
        // For eg, after adding the first row, increase rLo by 1
        //
        // The remaining valid rectangle (or square) keeps shrinking
        // as the limits close on each other
        //
        // Initial rectangle is
        // a b c d
        // e f g h
        // i j k l
        //
        // After adding first row, valid rectangle is
        // e f g h
        // i j k l
        // Output list is: [a, b, c, d]
        //
        // After adding last col, valid rectangle is
        // e f g
        // i j k
        // Output list is: [a, b, c, d, h, l]
        //
        // After adding last row, valid rectangle is
        // e f g
        // Output list is: [a, b, c, d, h, l, k, j, i]
        //
        // After adding first col, valid rectangle is
        // f g
        // Output list is: [a, b, c, d, h, l, k, j, i, e]
        //
        // After adding first row, valid rectangle is
        // <empty>
        // Output list is: [a, b, c, d, h, l, k, j, i, e, f, g]
        int rLo = 0;
        int rHi = m - 1;
        int cLo = 0;
        int cHi = n - 1;
        while (true) {
            try {
                addFirstRow(output, matrix, rLo, rHi, cLo, cHi);
                rLo++;

                addLastCol(output, matrix, rLo, rHi, cLo, cHi);
                cHi--;

                addLastRow(output, matrix, rLo, rHi, cLo, cHi);
                rHi--;

                addFirstCol(output, matrix, rLo, rHi, cLo, cHi);
                cLo++;
            } catch (InvalidAlgorithmParameterException e) {
                return output;
            }
        }
    }

    private void checkValidity(int rLo, int rHi, int cLo, int cHi) throws InvalidAlgorithmParameterException {
        if (rLo > rHi || cLo > cHi)
            throw new InvalidAlgorithmParameterException();
    }

    private void addFirstRow(List<Integer> output, int[][] matrix, int rLo, int rHi, int cLo, int cHi)
            throws InvalidAlgorithmParameterException {
        checkValidity(rLo, rHi, cLo, cHi);
        for (int c = cLo; c <= cHi; c++) {
            output.add(matrix[rLo][c]);
        }
    }

    private void addLastCol(List<Integer> output, int[][] matrix, int rLo, int rHi, int cLo, int cHi)
            throws InvalidAlgorithmParameterException {
        checkValidity(rLo, rHi, cLo, cHi);
        for (int r = rLo; r <= rHi; r++) {
            output.add(matrix[r][cHi]);
        }
    }

    private void addLastRow(List<Integer> output, int[][] matrix, int rLo, int rHi, int cLo, int cHi)
            throws InvalidAlgorithmParameterException {
        checkValidity(rLo, rHi, cLo, cHi);
        for (int c = cHi; c >= cLo; c--) {
            output.add(matrix[rHi][c]);
        }
    }

    private void addFirstCol(List<Integer> output, int[][] matrix, int rLo, int rHi, int cLo, int cHi)
            throws InvalidAlgorithmParameterException {
        checkValidity(rLo, rHi, cLo, cHi);
        for (int r = rHi; r >= rLo; r--) {
            output.add(matrix[r][cLo]);
        }
    }
}
