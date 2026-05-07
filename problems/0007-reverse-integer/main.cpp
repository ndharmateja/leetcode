#include <limits>

class Solution
{
private:
    // int_min_val = -2147483648
    // int_max_val_by_10 = 2147483647 / 10 = 214748364
    static inline const int int_min_val = std::numeric_limits<int>::min();
    static inline const int int_max_val_by_10 = std::numeric_limits<int>::max() / 10;

    /**
     * Iterative solution
     * Theta(log x) [= Theta(1) as log x <= 10] time
     * Theta(1) space
     */
    static int solution1(int x)
    {
        // If x is int_min_val itself, it has no absolute value
        // and the reverse is too large, so we can return 0
        if (x == int_min_val || x == 0)
            return 0;

        // Store if x is negative and store only the absolute value of x
        bool is_negative{false};
        if (x < 0)
        {
            is_negative = true;
            x = -x;
        }

        // Accumulate the result digit by digit
        int result{0}, digit;
        while (x)
        {
            // Extract the rightmost digit
            digit = x % 10;
            x = x / 10;

            // Check for overflow before doing the calculation
            // If result == 214748364 and digit > 7, then it will overflow as max value is 2147483647
            // If result > 214748364 then 10 * result itself will overflow
            if (result > int_max_val_by_10 || (result == int_max_val_by_10 && digit > 7))
                return 0;

            // "Append" digit to the end of the result
            result = result * 10 + digit;
        }

        // Return the result accounting for the negative sign
        return is_negative ? -result : result;
    }

public:
    int reverse(int x) { return solution1(x); }
};