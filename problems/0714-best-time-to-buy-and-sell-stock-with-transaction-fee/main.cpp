#include <vector>
#include <algorithm>

class Solution
{
private:
    static int sol1(const std::vector<int> &prices, const int fee)
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
         * without[1] = max{ 0, (prices[1] - prices[0]) - fee }
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
         * by buying it on day 0 and selling it on day 1 if it makes a profit (after the transaction fee)
         * so the max profit is max{ 0, (prices[1] - prices[0]) - fee }
         * * Recurrence relation
         *    with[i] = max{ with[i-1], without[i-1] - prices[i] }
         * without[i] = max{ without[i-1], (without[i-1] + prices[i]) - fee}
         * The max profit we can have at the end of day 'i' by holding the stock is
         * by holding the stock on the previous day and not selling it on day 'i'
         * or by not having the stock on day i-2 (we can't use day i-1 due to cooldown)
         * and buying it on day 'i'. So we take the max between the two.
         * The max profit we can have at the end of day without holding the stock is
         * by not holding the stock on the previous day and not buying it on day 'i'
         * or by having the stock on day i-1 and selling it on day 'i' by paying the transaction fee.
         * So we take the max between the two.
         * * Order of filling
         * We can fill the table from left to right as ith day's values only depend upon
         * the values of i-1
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
        without[1] = std::max(0, (prices[1] - prices[0]) - fee);

        // Fill the table from left to right and return the result
        for (int i = 2; i < n; i++)
        {
            with[i] = std::max(with[i - 1], without[i - 1] - prices[i]);
            without[i] = std::max(without[i - 1], with[i - 1] + prices[i] - fee);
        }
        return without[n - 1];
    }

    /**
     * Space optimized version of solution 1
     *
     * Theta(n) time and Theta(1) space
     */
    static int sol2(const std::vector<int> &prices, const int fee)
    {
        int n{static_cast<int>(prices.size())};
        if (n == 1)
            return 0;

        // Base case, start with values for i=1
        int with_stock{-std::min(prices[0], prices[1])};
        int without_stock{std::max(0, (prices[1] - prices[0]) - fee)};
        for (int i = 2; i < n; i++)
        {
            int new_with_stock = std::max(with_stock, without_stock - prices[i]);
            int new_without_stock = std::max(without_stock, with_stock + prices[i] - fee);
            with_stock = new_with_stock;
            without_stock = new_without_stock;
        }
        return without_stock;
    }

public:
    int maxProfit(const std::vector<int> &prices, int fee) const { return sol1(prices, fee); }
};