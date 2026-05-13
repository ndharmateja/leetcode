#include <vector>

class Solution
{
private:
    /**
     * Bottom up DP solution
     *
     * Theta(n) time and Theta(n) space
     */
    static int sol1(const std::vector<int> &prices)
    {
        /**
         * * DP Solution
         * with[i]   : The max profit we can have at the end of day 'i' by holding the stock
         *             at the end of the day 'i'
         * without[i]: The max profit we can have at the end of day 'i' without the stock
         *             at the end of the day 'i'
         * * Base case
         * with[0] = -prices[0]
         * with[1] = -min{ prices[0], prices[1] }
         * without[0] = 0
         * without[1] = max{ 0, prices[1] - prices[0] }
         * At end of day 0,
         * the max profit we can have by holding the stock is by buying the stock on day 0
         * there is no other option, so the max profit is -prices[0] (we would have a negative
         * profit as we bought the stock)
         * the max profit we can have without holding the stock is by not buying it
         * so the max profit is 0
         * At end of day 1,
         * the max profit we can have by holding the stock is by buying the stock on day 0
         * or day 0 (whichever is smaller), so the max profit is -min{ prices[0], prices[1] }
         * the max profit we can have without holding the stock is by not buying it or
         * by buying it on day 0 and selling it on day 1 if it makes a profit
         * so the max profit is max{ 0, prices[1] - prices[0] }
         * * Recurrence relation
         *    with[i] = max{ with[i-1], without[i-2] - prices[i] }
         * without[i] = max{ without[i-1], without[i-1] + prices[i] }
         * The max profit we can have at the end of day 'i' by holding the stock is
         * by holding the stock on the previous day and not selling it on day 'i'
         * or by not having the stock on day i-2 (we can't use day i-1 due to cooldown)
         * and buying it on day 'i'. So we take the max between the two.
         * The max profit we can have at the end of day without holding the stock is
         * by not holding the stock on the previous day and not buying it on day 'i'
         * or by having the stock on day i-1 and selling it on day 'i'.
         * So we take the max between the two.
         * * Order of filling
         * We can fill the table from left to right as ith day's values only depend upon
         * the values of i-1 and i-2
         * * Final answer
         * without[n-1] which is the max profit we can have by not having the stock
         * at the end of the last day
         * * Running time
         * #subproblems: 2 * n
         * work per subproblem: Theta(1)
         * postprocessing: Theta(1)
         * total running time: Theta(n)
         */
        // Edge case
        // If the #days is 1, we don't have enough time to buy and sell
        // so the profit is 0
        int n{static_cast<int>(prices.size())};
        if (n == 1)
            return 0;

        // Create the DP arrays and fill the base cases
        std::vector<int> with(n), without(n);
        with[0] = -prices[0];
        without[0] = 0;
        with[1] = -std::min(prices[0], prices[1]);
        without[1] = std::max(0, prices[1] - prices[0]);

        // Fill the table from left to right and return the result
        for (int i = 2; i < n; i++)
        {
            with[i] = std::max(with[i - 1], without[i - 2] - prices[i]);
            without[i] = std::max(without[i - 1], with[i - 1] + prices[i]);
        }
        return without[n - 1];
    }

    /**
     * Space optimized version of solution 1
     */
    static int sol2(const std::vector<int> &prices)
    {
        int n{static_cast<int>(prices.size())};
        if (n == 1)
            return 0;
        int with_stock_curr{-std::min(prices[0], prices[1])};
        int without_stock_prev{0}, without_stock_curr{std::max(0, prices[1] - prices[0])};

        for (int i = 2; i < n; i++)
        {
            int with_stock = std::max(with_stock_curr, without_stock_prev - prices[i]);
            int without_stock = std::max(without_stock_curr, with_stock_curr + prices[i]);
            with_stock_curr = with_stock;
            without_stock_prev = without_stock_curr;
            without_stock_curr = without_stock;
        }
        return without_stock_curr;
    }

public:
    int maxProfit(const std::vector<int> &prices) { return sol2(prices); }
};