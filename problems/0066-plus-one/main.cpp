#include <vector>

class Solution
{
public:
    std::vector<int> plusOne(std::vector<int> digits)
    {
        // We are using the copy vector passed to the function
        // to store the result and return it so that we don't create a new one

        // Use reverse iterators
        for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        {
            // If number itself is less than 9, then we can increment and be done with it
            if (*it < 9)
            {
                (*it)++;
                return digits;
            }

            // Otherwise, we make the current digit 0 and continue with the next iteration
            // where carry will be 1, which is why we are directly incrementing the digit
            // by 1
            *it = 0;
        }

        // If we reach this point, it means that the carry is 1 at the end
        // (because we'd have returned from the function if that is not the case)
        // So we insert 1 at the start of the vector (Theta(n) operation but better
        // than reversing the vector twice)
        digits.insert(digits.begin(), 1);
        return digits;
    }
};