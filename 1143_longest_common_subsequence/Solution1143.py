class Solution1143:
    def lcs_helper(self, text1: str, text2: str, memo: dict) -> int:
        if len(text1) == 0 or len(text2) == 0:
            return 0
        key = (len(text1), len(text2))
        if key not in memo:
            val1 = self.lcs_helper(text1[:-1], text2, memo)
            val2 = self.lcs_helper(text1, text2[:-1], memo)
            val3 = self.lcs_helper(text1[:-1], text2[:-1], memo)
            if text1[-1] == text2[-1]:
                memo[key] = max(val1, val2, val3 + 1)
            else:
                memo[key] = max(val1, val2, val3)
        return memo[key]

    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        return self.lcs_helper(text1, text2, {})
