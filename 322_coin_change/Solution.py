from typing import List


class Solution:
    def coinChangeHelper(self, coins, amount, memo):
        if amount == 0:
            return 0
        if amount not in memo:
            min_value = float("inf")
            updated = False
            for coin in coins:
                if amount < coin:
                    continue
                prev_min_value = self.coinChangeHelper(coins, amount - coin, memo)
                if prev_min_value == -1:
                    continue
                if prev_min_value < min_value:
                    min_value = prev_min_value
                    updated = True
            if updated:
                memo[amount] = min_value + 1
            else:
                memo[amount] = -1

        return memo[amount]

    def coinChange(self, coins: List[int], amount: int) -> int:
        return self.coinChangeHelper(coins, amount, {})