class Solution:
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

    def solution1(self, text1: str, text2: str) -> int:
        return self.lcs_helper(text1, text2, {})

    def solution2(self, text1: str, text2: str) -> int:
        m = len(text1)
        n = len(text2)
        memo = {}

        def dfs(i, j):
            if i == m or j == n:
                return 0
            if (i, j) in memo:
                return memo[(i, j)]

            if text1[i] == text2[j]:
                result = 1 + dfs(i + 1, j + 1)
            else:
                result = max(dfs(i + 1, j), dfs(i, j + 1))
            memo[(i, j)] = result
            return result

        return dfs(0, 0)

    def solution3(self, text1: str, text2: str) -> int:
        m = len(text1)
        n = len(text2)
        dp = [[0 for j in range(n + 1)] for i in range(m + 1)]

        dp[m][n] = 0
        for i in range(m):
            dp[i][n] = 0
        for i in range(n):
            dp[m][i] = 0

        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if text1[i] == text2[j]:
                    dp[i][j] = 1 + dp[i + 1][j + 1]
                else:
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1])

        return dp[0][0]

    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        return self.solution3(text1, text2)
