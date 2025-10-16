from typing import List


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        memo = {}

        def dfs(i, target2):
            # Base case
            # If we reach the end with a target2 of 0, then
            # it means that we were able to achieve the original target
            # so we return 1 as this is one such way
            if i == n:
                if target2 == 0:
                    return 1
                return 0

            # If the result is already computed and stored, return it
            if (i, target2) in memo:
                return memo[(i, target2)]

            # We have 2 choices for each number
            # We either use the number with + sign or - sign

            # If we use it with + sign, then the target2 reduces by the current
            # number, so we see the number of solutions for nums[i + 1:] with
            # target2 as target2 - nums[i]
            result_positive_sign = dfs(i + 1, target2 - nums[i])

            # If we use it with - sign, then the target2 increases by the current
            # number, so we see the number of solutions for nums[i + 1:] with
            # target2 as target2 + nums[i]
            result_negative_sign = dfs(i + 1, target2 + nums[i])

            # Store the result and return the result
            result = result_positive_sign + result_negative_sign
            memo[(i, target2)] = result
            return result

        return dfs(0, target)


s = Solution()
print(s.findTargetSumWays([1, 1, 1, 1, 1], 3))
