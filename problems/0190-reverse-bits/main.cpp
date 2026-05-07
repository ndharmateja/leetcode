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
        // Only 31 iterations are needed as the first and last bits are guaranteed to be 0
        // according to the leetcode constraints
        uint32_t result{0};
        for (int i = 0; i < 31; i++)
        {
            result |= (n & 1) << (31 - i);
            n >>= 1;
        }
        return result;
    }

    /**
     * "Divide and Conquer"-istic approach
     * 5 "iterations" instead of 31/32 for the above solutions
     */
    static uint32_t solution3(uint32_t n)
    {
        /**
         * Explanation:
         * Swap adjacent bit groups of sizes 1, 2, 4, 8, 16
         *
         * Eg: abcdefgh
         * After swapping adjacent bit groups of size 1, we have badcfehg
         * After swapping adjacent bit groups of size 2, we have dcbahgfe
         * After swapping adjacent bit groups of size 4, we have hgfedcba
         */

        // Modifying the input 'n' itself to store the result
        // Swap adjacent bit groups of size 1
        // Eg: abcdefgh, 10101010 = 0xAA
        // ((abcdefgh & 10101010) >> 1) | ((abcdefgh << 1) & 10101010)
        // = (a0c0e0g0 >> 1) | (bcdefgh0 & 10101010)
        // = 0a0c0e0g | b0d0f0h0
        // = badcfehg
        n = ((n & 0xAAAAAAAA) >> 1) | ((n << 1) & 0xAAAAAAAA);

        // Swap adjacent bit groups of size 2
        // Eg: abcdefgh, 11001100 = 0xCC
        // ((abcdefgh & 11001100) >> 2) | ((abcdefgh << 2) & 11001100)
        // = (ab00ef00 >> 2) | (cdefgh00 & 11001100)
        // = 00ab00ef | cd00gh00
        // = cdabghef
        n = ((n & 0xCCCCCCCC) >> 2) | ((n << 2) & 0xCCCCCCCC);

        // Swap adjacent bit groups of size 4
        // Eg: abcdefgh, 11110000 = 0xF0
        // ((abcdefgh & 11110000) >> 4) | ((abcdefgh << 4) & 11110000)
        // = (abcd0000 >> 4) | (efgh0000 & 11110000)
        // = 0000abcd | efgh0000
        // = efghabcd
        n = ((n & 0xF0F0F0F0) >> 4) | ((n << 4) & 0xF0F0F0F0);

        // Swap adjacent bit groups of size 8
        n = ((n & 0xFF00FF00) >> 8) | ((n << 8) & 0xFF00FF00);

        // Swap adjacent bit groups of size 16
        n = ((n & 0xFFFF0000) >> 16) | ((n << 16) & 0xFFFF0000);

        // Return the result
        return n;
    }

public:
    uint32_t reverseBits(uint32_t n) { return solution3(n); }
};