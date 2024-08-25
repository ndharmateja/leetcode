public class Solution521 {
    // O(n) time and O(1) space solution
    public int maxProfit(int[] prices) {
        if (prices.length == 1)
            return 0;

        int buy = 0;
        int sell = 1;
        int maxProfit = Math.max(prices[sell] - prices[buy], 0);

        while (true) {
            // If we reach the end, break
            if (sell == prices.length - 1)
                break;

            // If price of buy is greater than price of sell
            // increment both, as there is no profit there
            if (prices[buy] > prices[sell]) {
                buy++;
                sell++;
            }
            // If price of index after sell is less than the price of curr
            // buy index, we should buy there, so we make that the new buy
            else if (prices[sell + 1] < prices[buy]) {
                // Making sure that there are two elements after the sell
                if (sell == prices.length - 2) {
                    break;
                }
                // Update buy and sell accordingly
                else {
                    buy = sell + 1;
                    sell = sell + 2;
                }
            }
            // Simply update curr sell index
            else {
                sell++;
            }

            // Calculate the profit and update the maxProfit after the update
            maxProfit = Math.max(prices[sell] - prices[buy], maxProfit);
        }

        return maxProfit;
    }
}
