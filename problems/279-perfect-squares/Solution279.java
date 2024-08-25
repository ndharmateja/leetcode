import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution279 {
    private List<Integer> getPerfectSquaresList(int n) {
        List<Integer> perfectSquares = new ArrayList<>();
        int i = 1;
        int square;
        while ((square = i * i++) <= n) {
            perfectSquares.add(square);
        }
        return perfectSquares;
    }

    // DP solution using memoization
    // Similar to min number of coins problem
    // Instead of denominations, we subtract squares
    // O(n * sqrt(n)) time and O(n) space solution
    private int numSquares(int n, Map<Integer, Integer> memo, List<Integer> squares) {
        if (n == 0)
            return 0;
        if (!memo.containsKey(n)) {
            int minValue = Integer.MAX_VALUE;
            for (int square : squares) {
                // As squares are in increasing order
                // we can stop when we reach one square that is greater
                // than 'n' (because all the remaining squares
                // will be greater than 'n')
                if (square > n)
                    break;
                minValue = Math.min(minValue, numSquares(n - square, memo, squares) + 1);
            }
            memo.put(n, minValue);
        }
        return memo.get(n);
    }

    public int numSquares(int n) {
        return numSquares(n, new HashMap<>(), getPerfectSquaresList(n));
    }
}