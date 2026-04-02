#include <string>

class Solution
{
private:
    /**
     * Theta(n) worst case running time and Theta(1) space
     */
    static bool solution1(std::string s)
    {
        int l = 0;
        int r = s.size() - 1;
        while (l < r)
        {
            // If the left char is not alphanumeric, we can skip it
            // we skip it by incrementing l
            // If it is alphanumeric we don't increment l yet as the right
            // char could be non alphanumeric in which case we need to get the
            // char at l in the next iteration as well
            unsigned char cl = s[l];
            if (!std::isalnum(cl))
            {
                l++;
                continue;
            }

            unsigned char cr = s[r];
            if (!std::isalnum(cr))
            {
                r--;
                continue;
            }

            // Both chars are alphanumeric at this point
            // If they don't match, we can exit with false
            if (std::tolower(cl) != std::tolower(cr))
                return false;

            // If they match, then we need to update both pointers
            l++;
            r--;
        }

        // If we reach here it means that all the corresponding pairs of chars matched
        return true;
    }

    /**
     * Theta(n) worst case running time and Theta(1) space
     */
    static bool solution2(std::string s)
    {
        int l = 0;
        int r = s.size() - 1;
        while (l < r)
        {
            // Move the left pointer until we either cross the right pointer or
            // reach an alpha numeric char
            while (l < r && !std::isalnum(static_cast<unsigned char>(s[l])))
                l++;

            // Move the right pointer until we either cross the left pointer or
            // reach an alpha numeric char
            while (l < r && !std::isalnum(static_cast<unsigned char>(s[r])))
                r--;

            // Both chars are alphanumeric at this point
            // If they don't match, we can exit with false
            if (std::tolower(static_cast<unsigned char>(s[l])) !=
                std::tolower(static_cast<unsigned char>(s[r])))
                return false;

            // If they match, then we need to update both pointers
            l++;
            r--;
        }

        // If we reach here it means that all the corresponding pairs of chars matched
        return true;
    }

public:
    bool isPalindrome(std::string s) { return solution2(s); }
};