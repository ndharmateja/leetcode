class Solution70:

    def __init__(self):
        self.memo = {0: 1, 1: 1}

    def fibonacci(self, n):
        if n == 0 or n == 1:
            return 1
        x = 1
        y = 1
        for i in range(n - 1):
            value = x + y
            x = y
            y = value
        return y
        

    def climbStairs(self, n: int) -> int:
        return self.fibonacci(n)
