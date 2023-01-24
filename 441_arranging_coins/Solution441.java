@SuppressWarnings("unused")
class Solution441 {
    public int arrangeCoins(int n) {
        return solution2(n);
    }

    // O(1) time and O(1) space solution
    // solving for k in k(k+1)/2 = n
    // sum of 'k' natural numbers
    private int solution2(int n) {
        return (int) Math.floor((-1 + Math.sqrt(1 + 8 * ((long) n))) / ((double) 2));
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