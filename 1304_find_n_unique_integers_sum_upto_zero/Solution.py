from typing import List


class Solution:
    def sumZero(self, n: int) -> List[int]:
        return [-(x + 1) for x in range(n//2)] + [x + 1 for x in range(n//2)] + ([0] if n % 2 == 1 else [])
