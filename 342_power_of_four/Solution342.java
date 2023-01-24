@SuppressWarnings("unused")
class Solution342 {
    public boolean isPowerOfFour(int n) {
        return solution1(n);
    }

    // O(log n) time and O(log n) space (recursion) solution
    // Using recursion
    private boolean solution1(int n) {
        if (n == 0)
            return false;
        return ((n == 1) || (n % 4 == 0 && solution1(n / 4)));
    }

    // O(log n) time and O(1) space solution
    // Using loops
    private boolean solution2(int n) {
        if (n == 0)
            return false;
        while (n % 4 == 0)
            n /= 4;
        return n == 1;
    }
}