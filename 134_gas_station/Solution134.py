from typing import List

# O(n) time and O(1) space
# Reference: https://youtu.be/lJwbPZGo05A
class Solution134:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        # Compute the differences between 'gas' and 'cost'
        # and store it in 'gas' array itself
        # Also compute gas and cost totals
        total_gas = 0
        total_cost = 0
        for i, (g, c) in enumerate(zip(gas, cost)):
            total_gas += g
            total_cost += c
            gas[i] = g - c

        # If total cost is more than total gas we return -1
        if total_cost > total_gas:
            return -1

        # Start iterating the differences from left to right
        # keeping a track of total so far
        # At any point if total goes below zero
        # reset the total
        # And start at the next index
        # Also keep track of the start index
        # Once we reach the end of the differences array
        # we return the start index
        # We don't need to cycle over from the start again
        # because we know the total of gas >= total of cost
        # so the remaining elements [:start_index] sum will be enough
        total = 0
        start_index = 0
        for i, diff in enumerate(gas):
            if total + diff < 0:
                total = 0
                start_index = i + 1
            else:
                total += diff
        
        return start_index
