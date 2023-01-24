class Solution441 {
    public int arrangeCoins(int n) {
        return solution1(n);
    }

    // O(n) time and O(1) space solution
    private int solution1(int n) {
        int numRows = 0;
        while (n > 0) {
            // Current row length = numRows + 1
            if (n >= numRows + 1) {
                numRows++;
            }
            n -= numRows;
        }

        return numRows;
    }
}