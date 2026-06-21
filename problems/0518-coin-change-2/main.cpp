#include <vector>
#include <cctype>

class Solution
{
private:
    static void backtrack(const std::vector<int> &candidates, int target,
                          int candidate_start_index, int num_candidates,
                          std::vector<std::vector<int>> &result, std::vector<int> &buffer)
    {
        if (!target)
        {
            result.push_back(buffer);
            return;
        }

        if (target < 0)
            return;

        for (int i = candidate_start_index; i < num_candidates; i++)
        {
            int candidate = candidates[i];
            buffer.push_back(candidate);
            backtrack(candidates, target - candidate, i, num_candidates, result, buffer);
            buffer.pop_back();
        }
    }

    static std::vector<std::vector<int>>
    sol1(const std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> buffer;
        int num_candidates = static_cast<int>(candidates.size());
        backtrack(candidates, target, 0, num_candidates, result, buffer);
        return result;
    }

    static int dfs(const std::vector<int> &nums, int target, int i, int buffer_sum, std::vector<std::vector<int>> &memo)
    {

        // If the buffer_sum crosses the target, then there is no point continuing
        // as all the numbers are positive
        if (buffer_sum > target)
            return 0;

        // If we reach the end, we don't need to do anything
        // so we can simply return
        if (i == nums.size())
            return 0;

        // If targer sum is found, we can add this sequence to our result and exit
        int &result = memo[i][buffer_sum];
        if (result != -1)
            return result;

        if (buffer_sum == target)
            return (result = 1);

        // Two options pick the current one or don't pick the current one
        // 1. If we pick the current one, we add that to the current sum
        // and the current list to track the sequence and then
        // we call the dfs starting from *the same element* again
        // as each element can be picked multiple times
        // That is why we call dfs again from 'i' instead of 'i+1'
        result = 0;
        result += dfs(nums, target, i, buffer_sum + nums[i], memo);

        // 2. If we don't pick the current element, we call dfs starting from the
        // next element
        result += dfs(nums, target, i + 1, buffer_sum, memo);
        return result;
    }

    int sol2(int target, const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> memo(n, std::vector<int>(target + 1, -1));
        return dfs(nums, target, 0, 0, memo);
    }

    /**
     * Bottom up DP solution
     */
    int sol3(int T, const std::vector<int> &coins)
    {
        /**
         * * DP solution
         * dp[t][i] := the number ways we can form 't' using the first 'i' coins
         * (Idea is similar to solution1 of problem 39. Combination Sum where we
         * consider only "sorted" combinations where the order of the elements in
         * the combination is same as that of nums but with the idea of max index
         * instead of min index there)
         * * Base cases
         * dp[0][i] = 1
         * dp[t][0] = 0 (for t > 0)
         * * Recurrence relation
         * dp[t][i] = dp[t][i-1] + dp[t-coins[i-1]][i]  if t >= coins[i-1]
         *          = dp[t][i-1]                        otherwise
         * If we use the ith coin (ith coin is coins[i-1]), we can still use any of the first 'i' coins
         * as repetition is allowed, but if we don't use the ith coin we should
         * only be using the first i-1 coins (to maintain the combination sum subsequence idea).
         * * Order of filling
         * Row by row from top to bottom, filling each row from left to right
         * * Final answer
         * dp[T][n] where T is the target and n is the number of coins
         * * Running time
         * #subproblems        = (n + 1)(T + 1)
         * work per subproblem = Theta(1)
         * total running time  = Theta(nT) which is pseudopolynomial as lg(T) is the size of input
         */

        // ! Note: even though the leetcode constraints explicitly mention that the result is
        // ! going to fit in a 32 bit signed integer, there could be cases where the intermediate
        // ! values could overflow. Eg: the target is odd and all the coins are only even
        // ! 64 bit and even 128 bit signed integers won't work
        // ! which is why we are using a 128 bit unsigned integer
        // ! This is the reason why the top down solution is better as it would only compute
        // ! intermediate results that are necessary for the final result

        // Create the dp table
        int n{static_cast<int>(coins.size())};
        std::vector<std::vector<__uint128_t>> dp(T + 1, std::vector<__uint128_t>(n + 1));

        // Base cases
        // All values are zero initialized in the vector, so we don't need to
        // explicitly set dp[t][0] = 0
        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        // Fill the table
        for (int t = 1; t <= T; t++)
            for (int i = 1; i <= n; i++)
            {
                int coin = coins[i - 1];
                dp[t][i] = dp[t][i - 1] + (t >= coin ? dp[t - coin][i] : 0);
            }

        // Return the answer
        return static_cast<int>(dp[T][n]);
    }

    /**
     * Recursively (memoized) finds the number of ways in which we can form
     * the amount 't' using the first 'i' coins (coins[:i])
     */
    int get_num_coins_sol4(int t, int i,
                           const std::vector<int> &coins,
                           std::vector<std::vector<int>> &memo)
    {
        // If the answer is already in the memo, we return it
        int &result = memo[t][i];
        if (result != -1)
            return result;

        // ! Base cases are handled when the memo is created
        // General case
        int coin = coins[i - 1];
        result = get_num_coins_sol4(t, i - 1, coins, memo) +
                 (t >= coin ? get_num_coins_sol4(t - coin, i, coins, memo) : 0);
        return result;
    }

    /**
     * Top down (memoized) version of sol3
     */
    int sol4(int T, const std::vector<int> &coins)
    {

        // Create the memo with -1 values
        int n{static_cast<int>(coins.size())};
        std::vector<std::vector<int>> memo(T + 1, std::vector<int>(n + 1, -1));

        // Fill the base cases
        for (int i = 0; i <= n; i++)
            memo[0][i] = 1;
        for (int t = 1; t <= T; t++)
            memo[t][0] = 0;

        // Return the answer
        return get_num_coins_sol4(T, n, coins, memo);
    }

    /**
     * Bottom up DP solution
     * Same as solution 3, but with i and t dimensions interchanged so that
     * it could be space optimized
     */
    int sol5(int T, const std::vector<int> &coins)
    {
        /**
         * * DP solution
         * dp[i][t] := the number ways we can form 't' using the first 'i' coins
         * (Idea is similar to solution1 of problem 39. Combination Sum where we
         * consider only "sorted" combinations where the order of the elements in
         * the combination is same as that of nums but with the idea of max index
         * instead of min index there)
         * * Base cases
         * dp[i][0] = 1
         * dp[0][t] = 0 (for t > 0)
         * * Recurrence relation
         * dp[i][t] = dp[i-1][t] + dp[i][t-coins[i-1]]  if t >= coins[i-1]
         *          = dp[i-1][t]                        otherwise
         * If we use the ith coin (ith coin is coins[i-1]), we can still use any of the first 'i' coins
         * as repetition is allowed, but if we don't use the ith coin we should
         * only be using the first i-1 coins (to maintain the combination sum subsequence idea).
         * * Order of filling
         * Row by row from top to bottom, filling each row from left to right
         * * Final answer
         * dp[n][T] where T is the target and n is the number of coins
         * * Running time
         * #subproblems        = (n + 1)(T + 1)
         * work per subproblem = Theta(1)
         * total running time  = Theta(nT) which is pseudopolynomial as lg(T) is the size of input
         */

        // ! Note: even though the leetcode constraints explicitly mention that the result is
        // ! going to fit in a 32 bit signed integer, there could be cases where the intermediate
        // ! values could overflow. Eg: the target is odd and all the coins are only even
        // ! 64 bit and even 128 bit signed integers won't work
        // ! which is why we are using a 128 bit unsigned integer
        // ! This is the reason why the top down solution is better as it would only compute
        // ! intermediate results that are necessary for the final result

        // Create the dp table
        int n{static_cast<int>(coins.size())};
        std::vector<std::vector<__uint128_t>> dp(n + 1, std::vector<__uint128_t>(T + 1));

        // Base cases
        // All values are zero initialized in the vector, so we don't need to
        // explicitly set dp[t][0] = 0
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        // Fill the table
        for (int i = 1; i <= n; i++)
            for (int t = 1; t <= T; t++)
            {
                int coin = coins[i - 1];
                dp[i][t] = dp[i - 1][t] + (t >= coin ? dp[i][t - coin] : 0);
            }

        // Return the answer
        return static_cast<int>(dp[n][T]);
    }

    /**
     * Recursively (memoized) finds the number of ways in which we can form
     * the amount 't' using the first 'i' coins (coins[:i])
     */
    int get_num_coins_sol6(int i, int t,
                           const std::vector<int> &coins,
                           std::vector<std::vector<int>> &memo)
    {
        // If the answer is already in the memo, we return it
        int &result = memo[i][t];
        if (result != -1)
            return result;

        // ! Base cases are handled when the memo is created
        // General case
        int coin = coins[i - 1];
        result = get_num_coins_sol6(i - 1, t, coins, memo) +
                 (t >= coin ? get_num_coins_sol6(i, t - coin, coins, memo) : 0);
        return result;
    }

    /**
     * Top down (memoized) version of sol5
     */
    int sol6(int T, const std::vector<int> &coins)
    {

        // Create the memo with -1 values
        int n{static_cast<int>(coins.size())};
        std::vector<std::vector<int>> memo(n + 1, std::vector<int>(T + 1, -1));

        // Fill the base cases
        for (int i = 0; i <= n; i++)
            memo[i][0] = 1;
        for (int t = 1; t <= T; t++)
            memo[0][t] = 0;

        // Return the answer
        return get_num_coins_sol6(n, T, coins, memo);
    }

    /**
     * Space optimized bottom up DP solution (corresponding to solution 5)
     */
    int sol7(int T, const std::vector<int> &coins)
    {
        // Create the dp table
        int n{static_cast<int>(coins.size())};
        std::vector<__uint128_t> dp(T + 1);

        // Base cases
        // All values are zero initialized in the vector, so we don't need to
        // explicitly set dp[t][0] = 0
        dp[0] = 1;

        // Fill the table
        // ! Optimization:
        // ! For each t=1 to t=T, we have in the inner loop
        // ! dp[t] = dp[t] + (t >= coin ? dp[t - coin] : 0)
        // ! For each t=1 to t=coin-1, dp[t] will remain as dp[t]
        // ! so we can directly start from t=coin to t=T and don't need to check if t >= coin
        for (int coin : coins)
            for (int t = coin; t <= T; t++)
                dp[t] = dp[t] + dp[t - coin];

        // Return the answer
        return static_cast<int>(dp[T]);
    }

public:
    int change(int amount, const std::vector<int> &coins) { return sol7(amount, coins); }
};