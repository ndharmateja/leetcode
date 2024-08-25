class Solution7:
    def reverse(self, x: int) -> int:
        is_negative = x < 0
        if is_negative:
            x = -x
        x = int(str(x)[::-1])
        if is_negative:
            x = -x
        if -2 ** 31 <= x and x <= 2 ** 31-1:
            return x
        else:
            return 0
