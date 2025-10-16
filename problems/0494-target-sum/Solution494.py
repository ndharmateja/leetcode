from typing import List


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        memo = {}

        def dfs(i, sum):
            # Base case
            # If we reach the end with sum == target
            # then we return 1 as this is one such way
            if i == n:
                if sum == target:
                    return 1
                return 0

            # If the result is already computed and stored, return it
            if (i, sum) in memo:
                return memo[(i, sum)]

            # We have 2 choices for each number
            # We either use the number with + sign or - sign

            # If we use it with + sign, then the sum increases by the current
            # number, so we see the number of solutions for nums[i + 1:] with
            # sum as sum + nums[i]
            result_positive_sign = dfs(i + 1, sum + nums[i])

            # If we use it with - sign, then the sum decreases by the current
            # number, so we see the number of solutions for nums[i + 1:] with
            # sum as sum - nums[i]
            result_negative_sign = dfs(i + 1, sum - nums[i])

            # Store the result and return the result
            result = result_positive_sign + result_negative_sign
            memo[(i, sum)] = result
            return result

        return dfs(0, 0)


s = Solution()
print(s.findTargetSumWays([1, 1, 1, 1, 1], 3))
