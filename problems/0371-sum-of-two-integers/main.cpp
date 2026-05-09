class Solution
{
private:
    /**
     * Testing leetcode by using '+'
     */
    static int solution1(int a, int b) { return a + b; }

    /**
     * Bitwise operators solution
     */
    static int solution2(int num1, int num2)
    {
        // Table for adding (d1 + d2 + carry) = {sum, carry}
        //  d1  d2 carry | sum  carry
        //  0   0    0   |  0     0
        //  0   0    1   |  1     0
        //  0   1    0   |  1     0
        //  0   1    1   |  0     1
        //  1   0    0   |  1     0
        //  1   0    1   |  0     1
        //  1   1    0   |  0     1
        //  1   1    1   |  1     1
        // sum   = (~d1 & ~d2 & carry) | (~d1 & d2 & ~carry) | (d1 & ~d2 & ~carry) | (d1 & d2 & carry)
        // carry = (~d1 & d2 & carry) | (d1 & ~d2 & carry) | (d1 & d2 & ~carry) | (d1 & d2 & carry)
        int result{0};
        int sum, carry{0};
        int d1, d2, i;

        // We only need to run the loop for a max of 32 times as that is the number of bits in an int
        // Before that if both num1 and num2 become 0 then we have run out of bits to add
        // This is a generic version and handles negative numbers as well
        // We need to check i < 32 as well to run the loop max 32 times
        // because if num1 is -1 it never becomes 0 as right shift would be arithmetic
        for (i = 0; i < 32 && (num1 || num2); i++)
        {
            // Get the last digits
            d1 = num1 & 1;
            d2 = num2 & 1;

            // Get the sum and carry
            sum = (~d1 & ~d2 & carry) | (~d1 & d2 & ~carry) | (d1 & ~d2 & ~carry) | (d1 & d2 & carry);
            carry = (~d1 & d2 & carry) | (d1 & ~d2 & carry) | (d1 & d2 & ~carry) | (d1 & d2 & carry);

            // Add the sum bit to the ith place in the result
            //               i=7
            //                ↓
            // Say result = 0001001101
            // and sum = 1 and we need to make (i=7)th place as sum
            // result = result | (sum << 7) = 0001001101 || (1 << 7) = 0001001101 | 0010000000 = 0011001101
            result |= (sum << i);

            // Right shift both numbers to process the next place of bits
            num1 >>= 1;
            num2 >>= 1;
        }

        // At the end if we have carry left over, we need to put that in the ith place
        // Right now i is either 32, in which case all bits are done and we can discard
        // the extra carry bit
        // If i < 32, say i=7, then it means that we processed the bits from i=0 to i=6
        // and now we need to place the carry (could be 0 or 1) in the ith place
        // Since we have declared i outside the for loop, i will exactly have the value
        // we need at this point after incrementing in the last iteration of the loop
        if (i < 32)
            result |= (carry << i);
        return result;
    }

    static int solution3(unsigned a, unsigned b)
    {
        /**
         * Explanation:
         * Add the two bits at a time in each place to get the sum bits.
         * Similarly figure out the carry bits in each place.
         * The carry bits would have to be shifted left by one place, and then
         * we can add the numbers formed by the sum bits and the carry bits
         * to get the results (think recursion).
         *
         * We can model this as a state machine.
         * State: Pair of numbers (x, y)
         * Initial state: (a, b)
         * Transition: (x, y) -> (number formed by sum bits, number formed by carry bits << 1)
         * Invariant: For any state (x, y), x + y = a + b
         * Termination:
         * Derived variable: #1s in the number formed by carry bits
         * After the first transition, the carry bits could all be 1s
         * but we left shift by one place, so the #bits could be 31 max after the first transition
         * so now the carry number has a 0 in the last place so the new carry won't have a 1 in the last place
         * so when that new carry is shifted by one place to the left after the second transition
         * it would have two 0s at the end => atmost 30 0s
         * We could prove by induction that this is a decreasing natural valued derived variable.
         * so it terminates.
         *
         * Table for sum and carry
         *  d1  d2 | sum  carry
         *  0   0  |  0     0
         *  0   1  |  1     0
         *  1   0  |  1     0
         *  1   1  |  0     1
         *
         * sum   = d1 ^ d2
         * carry = d1 & d2
         *
         * Eg:
         *     a =  0111
         *     b =  1011
         * a + b = 10010 = 0010 as we discard the last carry bit
         *
         * (x=0111,
         *  y=1011)
         * sum = 1100, carry = 0011 << 1 = 0110
         *
         * (x=1100,
         *  y=0110)
         * sum = 1010, carry = 0100 << 1 = 1000
         *
         * (x=1010
         *  y=1000)
         * sum = 0010, carry = 1000 << 1 = 0000
         *
         * (x=0010,
         *  y=0000)
         * Answer is x=0010 as y=0000
         *
         * We are doing all the computations as unsigned ints so that
         * we don't have any undefined issues with shifting etc
         * and then cast the result to int at the end
         */
        unsigned carry;
        while (b)
        {
            carry = a & b;
            a = a ^ b;
            b = carry << 1;
        }
        return static_cast<int>(a);
    }

public:
    int getSum(int a, int b) { return solution3(a, b); }
};