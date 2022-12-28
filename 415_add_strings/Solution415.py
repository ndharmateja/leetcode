class Solution415:
    def addStrings(self, num1: str, num2: str) -> str:
        if (len(num1) > len(num2)):
            num1, num2 = num2, num1

        carry = 0
        output = ""

        for i in range(len(num1)):
            total = int(num1[len(num1) - i - 1]) + int(num2[len(num2) - i - 1]) + carry
            carry = total // 10
            output = str(total % 10) + output

        for i in range(len(num1), len(num2)):
            total = int(num2[len(num2) - i - 1]) + carry
            carry = total // 10
            output = str(total % 10) + output

        if carry != 0:
            output = str(carry) + output

        return output
