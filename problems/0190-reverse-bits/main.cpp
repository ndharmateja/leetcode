#include <cstdint>

class Solution
{
private:
    static uint32_t solution1(uint32_t n)
    {
        /**
         * Explanation: We keep accumulating the bits of n one by one from right to left
         * and form the result
         * Eg: n = 01111010
         * result = 00000000
         *
         * i = 0
         * result <<= 1 => result = 00000000
         * result = 00000000 | (01111010 & 1) = 00000000
         * n >>= 1 => n = 00111101
         *
         * i = 1
         * result <<= 1 => result = 00000000
         * result = 00000000 | (00111101 & 1) = 00000001
         * n >>= 1 => n = 00011110
         *
         * i = 2
         * result <<= 1 => result = 00000010
         * result = 00000010 | (00011110 & 1) = 00000010
         * n >>= 1 => n = 00001111
         *
         * i = 3
         * result <<= 1 => result = 00000100
         * result = 00000100 | (00001111 & 1) = 00000101
         * n >>= 1 => n = 00000111
         *
         * i = 4
         * result <<= 1 => result = 00001010
         * result = 00001010 | (00000111 & 1) = 00001011
         * n >>= 1 => n = 00000011
         *
         * i = 5
         * result <<= 1 => result = 00010110
         * result = 00010110 | (00000011 & 1) = 00010111
         * n >>= 1 => n = 00000001
         *
         * i = 6
         * result <<= 1 => result = 00101110
         * result = 00101110 | (00000001 & 1) = 00101111
         * n >>= 1 => n = 00000000
         *
         * i = 7
         * result <<= 1 => result = 01011110
         * result = 01011110 | (00000000 & 1) = 01011110
         *
         */

        // For each of the 32 bits, we accumulate the bits of n one by one
        uint32_t result{0};
        for (int i = 0; i < 32; i++)
        {
            // Move the result one bit to the left to make room for the next bit
            result <<= 1;

            // Accumulate the rightmost bit of n
            result |= n & 1;

            // Remove the rightmost bit of n
            n >>= 1;
        }
        return result;
    }
    /**
     * Similar to solution1 except we directly place the bits of n one by one
     * in the correct position of the result
     */
    static uint32_t solution2(uint32_t n)
    {
        uint32_t result{0};
        for (int i = 0; i < 31; i++)
        {
            result |= (n & 1) << (31 - i);
            n >>= 1;
        }
        return result;
    }

public:
    uint32_t reverseBits(uint32_t n) { return solution1(n); }
};