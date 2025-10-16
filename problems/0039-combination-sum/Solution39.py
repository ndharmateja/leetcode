from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        n = len(candidates)
        combinations = []

        def dfs(i, sum, sequence):
            print(f"{sequence}: {sum}")
            if sum > target:
                return

            if sum == target:
                combinations.append(sequence[:])
                return

            if i == n:
                return

            sequence.append(candidates[i])
            dfs(i, sum + candidates[i], sequence)
            sequence.pop()

            dfs(i + 1, sum, sequence)

        dfs(0, 0, [])
        return combinations


s = Solution()
print(s.combinationSum([2, 3, 6, 7], 7))
