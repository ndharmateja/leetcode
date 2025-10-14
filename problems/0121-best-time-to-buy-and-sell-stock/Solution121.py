class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        min_so_far = prices[0]
        max_profit = 0

        for i in range(1, len(prices)):
            profit = prices[i] - min_so_far
            if profit > max_profit:
                max_profit = profit

            if prices[i] < min_so_far:
                min_so_far = prices[i]

        return max_profit
