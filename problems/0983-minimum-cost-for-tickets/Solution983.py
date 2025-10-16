from typing import List


class Solution:

    # Even though the durations are fixed
    # we are using a list for durations so that
    # it becomes a generalized solution for any given 'durations' list
    def mincostTickets(self, days, costs, durations=[1, 7, 30]) -> int:
        # Initialize the memo
        n = len(days)
        memo = {}

        # DFS function that tells us the minimum cost from day at index i (inclusive)
        # to the last day
        def dfs(i):
            # Base case: if i is out of bounds, return 0
            if i >= n:
                return 0

            # If we have already calculated the minimum cost from day at index i (inclusive)
            # to the last day, return the value
            if i in memo:
                return memo[i]

            # For each duration find the day (say at j index) which is out of bounds for this duration
            # from the current day and calculate the minimum cost from j to the last day and add the cost
            # of the current duration
            # We do that for all the durations possible and we select the minimum among them
            # (the cost for the duration + the minimum cost from j to the last day)
            min_cost = float("inf")
            for duration, cost in zip(durations, costs):
                # Find the index 'j' that is out of bounds for the current duration
                j = i + 1
                while j < n and days[j] < days[i] + duration:
                    j = j + 1

                # If this cost is less than the min so far, we update it
                min_cost = min(min_cost, cost + dfs(j))

            # Store the minimum cost in the memo and return that result
            memo[i] = min_cost
            return memo[i]

        # dfs(0) computes the minimum cost from the first day to the last day
        return dfs(0)
