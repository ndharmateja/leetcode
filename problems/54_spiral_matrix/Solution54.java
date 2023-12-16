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
