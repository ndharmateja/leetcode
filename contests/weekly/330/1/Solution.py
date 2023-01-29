class Solution:
    def distinctIntegers(self, n: int) -> int:
        processed = set()
        to_process = set()

        to_process.add(n)
        while len(to_process) > 0:
            curr = to_process.pop()
            if curr in processed:
                continue
            for factor in self.get_factors(curr - 1):
                to_process.add(factor)
            processed.add(curr)

        return len(processed)

    def get_factors(self, x):
        factors = set()
        for i in range(2, x + 1):
            if x % i == 0:
                factors.add(i)
        return factors
