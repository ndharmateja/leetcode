#include <vector>

class Solution
{
private:
    static int sol1(const std::vector<int> &prices)
    {
        // Prices are in the range [0, 10000] according to leetcode constraints
        // so we can init min_so_far with 10000
        int min_so_far{10000}, max_profit{0};

        // For every price in the list, we first see if that value is the
        // minimum so far in all the elements we've seen so far including that element
        // If yes, then that price becomes the min so far
        // and this price can't be used for selling to make a profit, so we can continue
        // if this is the minimum so far
        for (int price : prices)
        {
            // If the current price becomes the minimum so far
            // we can update it and continue (optimization as we know that
            // selling at this price after buying at previous minimum so far
            // will give us a negative profit)
            if (price < min_so_far)
                min_so_far = price;

            // If it is not the minimum so far
            // We can see how much max profit we could make by selling it
            // with this price by buying it at minimum so far to maximize the profit
            else
                max_profit = std::max(max_profit, price - min_so_far);
        }

        // Return the maximum profit
        return max_profit;
    }

public:
    int maxProfit(const std::vector<int> &prices) { return sol1(prices); }
};