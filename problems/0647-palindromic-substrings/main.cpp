#include <string>
#include <vector>

class Solution
{
private:
    /**
     * Bottom up 2D DP solution
     * See problem 5 for more details
     *
     * Theta(n^2) time and space complexity
     */
    static int solution1(const std::string &s)
    {
        // Create a nxn DP array
        // dp[i][j] keeps track if s[i:j] is a palindrome (inclusive of i and j)
        int n{static_cast<int>(s.size())};
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));

        // Base case
        // All diagonal elements should be 1
        int total_palindromic_substrings{n};
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        // All length 2 strings are palindromes if they are same alphabets
        // We also keep track of the max length of the palindrome and where it ends
        for (int i = 1; i < n; i++)
        {
            dp[i - 1][i] = s[i - 1] == s[i];
            if (dp[i - 1][i])
                total_palindromic_substrings++;
        }

        // Fill the table
        // in increasing order of string lengths
        for (int len = 3; len <= n; len++)
            for (int i = len - 1; i < n; i++)
            {
                // We can check if s[i - (len-1): i] (inclusive) is a palindrome
                // by checking if dp[i - (len-1) + 1][i - 1] is true (which is checking
                // if the string after removing the first and last characters is a palindrome)
                // and checking if the first and last characters are the same
                dp[i - (len - 1)][i] = (s[i - (len - 1)] == s[i]) && dp[i - (len - 1) + 1][i - 1];
                if (dp[i - (len - 1)][i])
                    total_palindromic_substrings++;
            }

        // Get the substring ending at max_index(inclusive) of length max_value
        return total_palindromic_substrings;
    }

    /**
     * Space optimized bottom up 2D DP solution
     * by expanding around the centers
     *
     * Theta(n^2) time and Theta(1) space complexity
     */
    static int solution2(const std::string &s)
    {
        // Start at char at i and expand outwards to see if it is a palindrome
        // and if it is a palindrome
        // update the start and max_length of the largest palindrome
        int n{static_cast<int>(s.size())};
        int total_palindromic_substrings{n};
        int l, r;
        for (int i = 0; i < n; i++)
        {
            // odd lengthed palindromes
            // we can start with palindromes of length 3
            // as 1 lengthed palindrome is already recorded
            l = i - 1, r = i + 1;
            while (l >= 0 && r < n && s[l--] == s[r++])
                total_palindromic_substrings++;

            // even lengthed palindromes
            // We can start with palindromes of length 2
            l = i, r = i + 1;
            while (l >= 0 && r < n && s[l--] == s[r++])
                total_palindromic_substrings++;
        }

        // Return the total number of palindromic substrings
        return total_palindromic_substrings;
    }

public:
    int countSubstrings(const std::string &s) { return solution2(s); }
};