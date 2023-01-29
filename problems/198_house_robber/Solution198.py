from typing import List


class Solution198:
    def rob(self, nums: List[int]) -> int:
        incl = excl = 0
        for num in nums:
            incl, excl = excl + num, max(incl, excl)
        return max(incl, excl)
