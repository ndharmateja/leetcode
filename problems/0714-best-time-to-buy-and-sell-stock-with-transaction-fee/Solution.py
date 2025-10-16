from typing import List


class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        # Initialize the memo with the base cases
        n = len(prices)
        memo = {(n, True): 0, (n, False): 0}

        # dfs(i, can_buy=True) -> max profit (from day i to the last day) if we can buy at day i
        # dfs(i, can_buy=False) -> max profit (from day i to the last day) if we can sell at day i
        def dfs(i: int, can_buy: bool):
            # If the solution is already in the memo, return it
            if (i, can_buy) in memo:
                return memo[(i, can_buy)]

            # If we can buy on ith day, there are two cases
            # we can either buy the stock in which case profit = -prices[i] + dfs(i + 1, can_buy=False)
            # or we can just hold the stock in which case profit = dfs(i + 1, can_buy=True)
            if can_buy:
                profit_if_we_buy_today = -prices[i] + dfs(i + 1, can_buy=False)
                profit_if_we_just_hold = dfs(i + 1, can_buy=True)
                profit = max(profit_if_we_buy_today, profit_if_we_just_hold)

            # If we can sell on ith day (incurs a transaction fee), there are two cases
            # we can either sell the stock in which case profit = prices[i] - fee + dfs(i + 1, can_buy=True)
            # or we can just hold the stock in which case profit = dfs(i + 1, can_buy=False)
            else:
                profit_if_we_sell_today = prices[i] - fee + dfs(i + 1, can_buy=True)
                profit_if_we_just_hold = dfs(i + 1, can_buy=False)
                profit = max(profit_if_we_sell_today, profit_if_we_just_hold)

            # Store the result in the memo and return it
            memo[(i, can_buy)] = profit
            return profit

        # dfs(0, True) -> max profit (from day 0 to the last day) if we can buy on day 0
        return dfs(0, True)
