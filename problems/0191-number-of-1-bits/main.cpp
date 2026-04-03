class Solution
{
private:
    /**
     * Theta(lg n) time and Theta(1) space
     * goes through every bit and increments result if the bit is a 1
     * #iterations = #bits
     *
     * Changed the signature to take the input as unsigned because
     * right shift can be arithmetic for signed values
     */
    static int solution1(unsigned n)
    {
        int result{0};
        while (n)
        {
            result += (n & 1);
            n >>= 1;
        }
        return result;
    }

    /**
     * Theta(k) time and Theta(1) space
     * where k = #1s in the bit representation of n
     *
     * Brian Kernighan's algorithm
     * Faster than solution 1 as #iterations = #1s instead of all bits
     *
     * Changed the signature to take the input as unsigned because
     * right shift can be arithmetic for signed values
     */
    static int solution2(unsigned n)
    {
        int result{0};
        while (n)
        {
            // n & (n - 1) essentially makes the rightmost 1 into a 0 and keeps the remaining
            // number unchanged. This happens because when we subtract 1 from n
            // all the bits starting from the rightmost 1 till the end get flipped.
            // So we keep making the rightmost 1 into a 0 until the whole
            // number becomes 0. That is why this algo takes #iterations = #1s.
            // Eg: n = 11001100100
            // Iteration1: n = 11001100100, n-1 = 11001100011 => n & (n-1) = 11001100000
            // Iteration2: n = 11001100000, n-1 = 11001011111 => n & (n-1) = 11001000000
            // Iteration3: n = 11001000000, n-1 = 11000111111 => n & (n-1) = 11000000000
            // Iteration4: n = 11000000000, n-1 = 10111111111 => n & (n-1) = 10000000000
            // Iteration5: n = 10000000000, n-1 = 01111111111 => n & (n-1) = 00000000000
            // 5 iterations until all the bits became 0. => five 1s in the number
            n = n & (n - 1);
            result++;
        }
        return result;
    }

public:
    int hammingWeight(int n) { return solution2(static_cast<unsigned>(n)); }
};