import java.util.HashMap;

class Solution322 {
    public int coinChange(int[] coins, int amount, HashMap<Integer, Integer> memo) {
        if (amount == 0)
            return 0;
        if (!memo.containsKey(amount)) {
            int minValue = Integer.MAX_VALUE;
            for (int coin : coins) {
                if (amount < coin)
                    continue;
                int prevMinValue = coinChange(coins, amount - coin, memo);
                if (prevMinValue < 0)
                    continue;
                if (prevMinValue < minValue)
                    minValue = coinChange(coins, amount - coin, memo);
            }
            if (minValue == Integer.MAX_VALUE) {
                memo.put(amount, -1);
            } else {
                memo.put(amount, minValue + 1);
            }
        }
        return memo.get(amount);
    }

    public int coinChange(int[] coins, int amount) {
        return coinChange(coins, amount, new HashMap<>());
    }

}