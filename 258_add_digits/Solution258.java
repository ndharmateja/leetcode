@SuppressWarnings("unused")
class Solution258 {
    public int addDigits(int num) {
        return solution2(num);
    }

    // Keep totalling digits
    // and keep removing 9s from the total
    private int solution1(int num) {
        if (num == 0)
            return 0;
        int total = 0;
        while (num > 9) {
            int digit = num % 10;
            num = num / 10;
            total += digit + 9;
            total %= 9;
        }
        total += num + 9;
        total %= 9;

        return total == 0 ? 9 : total;
    }

    // Answer is remainder when divided by 9
    private int solution2(int num) {
        if (num == 0)
            return 0;

        int total = num % 9;
        return total == 0 ? 9 : total;
    }
}