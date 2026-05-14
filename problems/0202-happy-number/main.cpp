#include <unordered_set>

class Solution
{
private:
    static int sum_of_squares(int n)
    {
        // Instead of having to compute the squares of digits we can have a lookup table
        static constexpr int squares[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

        int result{0};
        while (n)
        {
            int digit = n % 10;
            result += squares[digit];
            n /= 10;
        }
        return result;
    }

    /**
     * Floyd's tortoise and hare solution
     */
    static bool sol1(int n)
    {
        // Run slow and fast pointers until they coincide
        int slow{n}, fast{n};
        do
        {
            slow = sum_of_squares(slow);
            fast = sum_of_squares(sum_of_squares(fast));
        } while ((slow != fast));

        // At this point slow will be equal to fast
        // If they are both 1 it means that it is a happy number
        // otherwise we found that there exists a cycle
        return fast == 1;
    }

    /**
     * Unordered set solution
     */
    static bool sol2(int n)
    {
        // Keep looping until it reaches 1 or we find that there is a loop
        std::unordered_set<int> seen;
        while (n != 1)
        {
            // If we come across a number that we've already seen, then we can return false
            // Otherwise we add the number to the set
            // ! if (seen.count(n))
            // !     return false;
            // ! seen.insert(n);
            // ! Instead of above code we can get away with just one hash fn computation
            auto [_, inserted] = seen.insert(n);
            if (!inserted)
                return false;

            // Update n
            n = sum_of_squares(n);
        }

        // We reach this only if n becomes 1, we can return true
        return true;
    }

public:
    bool isHappy(int n) { return sol1(n); }
};