#include <limits>

class Solution
{
private:
    inline static const int int_min_val = std::numeric_limits<int>::min();

    /**
     * Brute force iterative solution
     * The number of iterations of the for loop is n
     */
    static double solution1(double x, int n)
    {
        // Edge cases
        // 1. 1^n = 1
        // 2. (-1)^n = n is even ? 1 : -1
        // 3. 0^n = 0
        // 4. x^0 = 1
        if (x == 1)
            return 1;
        if ((x == -1) && (n & 1 == 0))
            return 1;
        if ((x == -1) && (n & 1 == 1))
            return -1;
        if (!x)
            return 0;
        if (!n)
            return 1;

        // If n is -2^31 which is INT_MIN, then -n would be undefined
        // so we handle it separately
        // x^(-2^31) = (1/x) * x^(-2^31+1)
        if (n == int_min_val)
            return solution1(x, n + 1) / x;

        // If n is negative we take the reciprocal of x^abs(n)
        bool is_n_negative{n < 0};
        if (is_n_negative)
            n = -n;

        // Accumulate the result
        double result{1};
        for (int i = 0; i < n; i++)
            result *= x;
        return is_n_negative ? (1 / result) : result;
    }

    /**
     * Iterative solution using Binary Exponentiation
     * The number of iterations of the for loop is lg(n) instead of n
     * in solution1
     */
    static double solution2(double x, int n)
    {
        // Edge cases
        // 1. 1^n = 1
        // 2. (-1)^n = n is even ? 1 : -1
        // 3. 0^n = 0
        // 4. x^0 = 1
        if (x == 1)
            return 1;
        if ((x == -1) && (n & 1 == 0))
            return 1;
        if ((x == -1) && (n & 1 == 1))
            return -1;
        if (!x)
            return 0;
        if (!n)
            return 1;

        // If n is -2^31 which is INT_MIN, then -n would be undefined
        // so we handle it separately
        // x^(-2^31) = (1/x) * x^(-2^31+1)
        // To avoid all the branching statements, we can recursively call this
        // function itself once
        if (n == int_min_val)
            return solution2(x, n + 1) / x;

        // If n is negative we take the reciprocal of x^abs(n)
        bool is_n_negative{n < 0};
        if (is_n_negative)
            n = -n;

        // Compute the result
        // At this point n > 0 => most significant bit is 0
        // so any right shifts would be logical
        /**
         * Explanation:
         * Eg: x=4, n=37
         * 37 = 00100101
         * 4^37 = 4^32 * 4^4 * 4^1
         *
         * We are essentially breaking down the n into sum of powers of 2
         * 4^1, 4^2, 4^4, 4^8, 4^16, 4^32, ...
         * The above terms can be easily computed
         * Each term is the square of the previous term
         *
         * So if we have a 1 bit in ith place (from the right)
         * we need to multiply 4^(2^i) to the result
         */
        double result{1}, power_of_2{x};
        while (n)
        {
            if (n & 1)
                result *= power_of_2;
            power_of_2 = power_of_2 * power_of_2;
            n >>= 1;
        }

        // Return the result based on the parity of n
        return is_n_negative ? (1 / result) : result;
    }

public:
    double myPow(double x, int n) { return solution1(x, n); }
};