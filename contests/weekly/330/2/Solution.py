class Solution:
    def __init__(self) -> None:
        self.VALUE = 1_000_000_007

    # (x ^ k) % p
    def pow(x, k, p):
        out = 1
        for _ in range(k):
            out = (out * x) % p
        return out

    def monkeyMove(self, n: int) -> int:
        return ((pow(2, n, self.VALUE) - 2) + self.VALUE) % self.VALUE
