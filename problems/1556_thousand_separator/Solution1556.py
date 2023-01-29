class Solution:
    def thousandSeparator(self, n: int) -> str:
        if n == 0:
            return 0
        n = str(n)
        n = ("0" * ((3 - (len(n) % 3)) % 3)) + str(n)
        separated = [n[i: i+3] for i in range(0, len(n), 3)]
        joined = ".".join(separated)
        while joined.startswith("0"):
            joined = joined[1:]
        return joined
