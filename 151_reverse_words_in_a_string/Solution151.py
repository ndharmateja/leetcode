class Solution151:
    def reverseWords(self, s: str) -> str:
        return " ".join(s.strip().split()[::-1])
