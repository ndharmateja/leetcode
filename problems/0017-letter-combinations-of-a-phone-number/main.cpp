#include <vector>
#include <string>

class Solution
{
private:
    static inline constexpr int power_of_4[] = {1, 4, 16, 64, 256};
    static inline constexpr std::string digit_to_chars_map[] = {"",
                                                                "", "abc", "def",
                                                                "ghi", "jkl", "mno",
                                                                "pqrs", "tuv", "wxyz"};

    /**
     * Invariant:
     * 1. buffer has idx number of characters and is a valid result using
     *   the digits[:idx]
     */
    static void explore(const std::string &digits, int idx, int num_digits,
                        std::string &buffer, std::vector<std::string> &result)
    {
        // If the idx reaches the number of digits then according to the invariant
        // the buffer's size is num_digits itself
        // So we can add this to the result
        if (idx == num_digits)
        {
            result.push_back(buffer);
            return;
        }

        // For each character in the current digit (which is digits[idx])
        // we add that character and explore further and remove the character
        for (unsigned char c : digit_to_chars_map[digits[idx] - '0'])
        {
            buffer.push_back(c);
            explore(digits, idx + 1, num_digits, buffer, result);
            buffer.pop_back();
        }
    }

    static std::vector<std::string> sol1(const std::string &digits)
    {
        // Base case:
        // If the digits string is empty then we can return an empty vector
        int num_digits{static_cast<int>(digits.size())};
        if (!num_digits)
            return {};

        // Create the result vector and the buffer
        // The max characters a digit can have is 4 (Eg: 9 -> wxyz) so the max size
        // of the result = 4 ^ num_digits and according to leetcode constraints num_digits <= 4
        // so max size of the result is 256
        // The buffer's max size will be num_digits itself
        std::vector<std::string> result;
        result.reserve(power_of_4[num_digits]);
        std::string buffer;
        buffer.reserve(4);

        // Explore starting from idx 0 and return the result
        explore(digits, 0, num_digits, buffer, result);
        return result;
    }

public:
    std::vector<std::string> letterCombinations(const std::string &digits) { return sol1(digits); }
};