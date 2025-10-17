import java.util.HashMap;

@SuppressWarnings("unused")
public class Solution714 {
    public int maxProfit(int[] prices, int fee) {
        return solution1(prices, fee);
    }

    // O(n) time and O(n) space
    // Bottom up dp approach
    private int solution1(int[] prices, int fee) {
        // dp array stores the following information
        // dp[0] - stores the max profit for each day such that
        // we are holding the stock at the end of the day
        // dp[0][i] - max profit from days 0..i such that
        // we are holding the stock at the end of the day

        // dp[1] - stores the max profit for each day such that
        // we are not holding the stock at the end of the day
        // dp[1][i] - max profit from days 0..i such that
        // we are not holding the stock at the end of the day
        int n = prices.length;
        int[][] dp = new int[2][n];

        // Base case:
        // dp["hold"][0] = dp[0][0] = -prices[0] as we can hold the stock
        // at the end of day 0 only if we buy it => profit is -prices[0]
        // dp["not_hold"][0] = dp[1][0] = 0 as we shouldn't buy anything on day 0
        // to not hold the stock at the end of day 0
        dp[0][0] = -prices[0];
        dp[1][0] = 0;

        for (int i = 1; i < n; i++) {
            // Computing dp["hold"][i]
            // To hold a stock at the end of day i:
            //
            // case 1:
            // we need to have already held the stock on day i-1 (in which
            // case we don't need to do anything on day i)
            // => dp["hold"][i-1] (or) dp[0][i-1]
            //
            // case 2:
            // we didn't hold the stock on day i-1 (in which case we need to
            // buy the stock on day i).
            // => dp["not_hold"][i-1] - prices[i] (or) dp[1][i-1] - prices[i]
            //
            // So we take the maximum between them to maximize profit
            // => dp["hold"][i] = max{dp["hold"][i-1], dp["not_hold"][i-1] - prices[i]} (or)
            // => dp[0][i] = max{dp[0][i-1], dp[1][i-1] - prices[i]}
            dp[0][i] = max(dp[0][i - 1], dp[1][i - 1] - prices[i]);

            // Computing dp["not_hold"][i]
            // To not hold a stock at the end of day i:
            //
            // case 1:
            // we should already not be holding the stock on day i-1 (in which
            // case we don't need to do anything on day i)
            // => dp[1][i-1]
            //
            // case 2:
            // we held the stock on day i-1 (in which case we need to
            // sell the stock on day i which incurs a fee).
            // => dp[0][i-1] + prices[i] - fee
            //
            // So we take the maximum between them to maximize profit
            // => dp["not_hold"][i] = max{dp["not_hold"][i-1], dp["hold"][i-1] + prices[i] -
            // fee}
            // => dp[1][i] = max{dp[1][i-1], dp[0][i-1] + prices[i] - fee}
            dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] + prices[i] - fee);
        }

        // At the end, the max profit after 'n' days will be stored in
        // dp["not_hold"][n-1] = dp[1][n-1] as we shouldn't be holding the stock
        // after all the days are finished
        return dp[1][n - 1];
    }

    // O(n) time and O(n) space
    // Space optimized version of solution 1 (read that for full details)
    // Where we only store the hold and not_hold profits of
    // only the previous day
    private int solution2(int[] prices, int fee) {
        int n = prices.length;
        int hold = -prices[0];
        int notHold = 0;

        for (int i = 1; i < n; i++) {
            int newHold = max(hold, notHold - prices[i]);
            int newNotHold = max(notHold, hold + prices[i] - fee);
            hold = newHold;
            notHold = newNotHold;
        }

        return notHold;
    }

    // Top down dp approach
    // corresponding to solution 1 (read that for more details)
    private int solution3(int[] prices, int fee) {
        int n = prices.length;
        Integer[][] dp = new Integer[2][n];

        // Put the base cases in the memo
        dp[0][0] = -prices[0];
        dp[1][0] = 0;

        return dfs(prices, fee, n - 1, false, dp);
    }

    private int dfs(int[] prices, int fee, int i, boolean isHeld, Integer[][] dp) {
        // Base cases are also include in the memo

        // If memo contains the result we return it
        // 0 - hold
        // 1 - not hold
        if (dp[isHeld ? 0 : 1][i] != null) {
            return dp[isHeld ? 0 : 1][i];
        }

        // General case
        // See solution 1 for more details
        int result;
        if (isHeld)
            result = max(dfs(prices, fee, i - 1, true, dp),
                    dfs(prices, fee, i - 1, false, dp) - prices[i]);
        else
            result = max(dfs(prices, fee, i - 1, false, dp),
                    dfs(prices, fee, i - 1, true, dp) + prices[i] - fee);

        // Put the result in the memo
        dp[isHeld ? 0 : 1][i] = result;
        return result;
    }

    private int max(int a, int b) {
        return a > b ? a : b;
    }
}
