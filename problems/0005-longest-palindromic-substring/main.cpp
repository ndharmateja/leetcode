#include <string>
#include <vector>

class Solution
{
private:
    /*
    !Invalid solution
    Doesn't work as we are not considering smaller lengths of palindromes that at end i-1
    for forming a palindrome that ends at i
    Eg: AAAA (fails for index 3)

    Bottom up DP solution
    static std::string solution1(std::string s)
    {
        * DP solution:
        dp[i]: length of the longest palindromic substring ending at index i in the string
        * Base case:
        dp[0] = 1
        * Recurrence relation:
        dp[i] = dp[i-1] + 2   if       (i-1) - dp[i-1] >= 0 and s[i] == s[(i-1) - dp[i-1]]
              = 3             else if  i - 2 >= 0           and s[i] == s[i-2]
              = 2             else if  s[i] == s[i-1]
              = 1             otherwise
        * Order of filling:
        from left to right as we only need the value on the left
        * Final answer:
        max_i = the index for which dp[i] is max
        max_length = dp[max_i]
        then the s[max_i + 1 - max_length: max_i + 1] is the longest palindromic substring
        int n{static_cast<int>(s.size())};
        std::vector<int> dp(n);

        Base case:
        dp[0] = 1;

        Fill the array from left to right
        int max_index{0}, max_length{1};
        for (int i = 1; i < n; i++)
        {
            int prev_value = dp[i - 1];
            if ((i - 1) - prev_value >= 0 && s[i] == s[(i - 1) - prev_value])
            dp[i] = prev_value + 2;
            else if (i - 2 >= 0 && s[i] == s[i - 2])
            dp[i] = 3;
            else if (s[i] == s[i - 1])
            dp[i] = 2;
            else
            dp[i] = 1;

            Keep track of the max value and index in the dp array
            if (dp[i] > max_length)
            {
                max_length = dp[i];
                max_index = i;
            }
        }

        Get the substring ending at max_index (inclusive) of length max_value
        return s.substr(max_index + 1 - max_length, max_length);
    }
    */

    /**
     * Bottom up 2D DP solution
     *
     * Theta(n^2) time and space complexity
     */
    static std::string solution1(const std::string &s)
    {
        // Create a nxn DP array
        // dp[i][j] keeps track if s[i:j] is a palindrome (inclusive of i and j)
        int n{static_cast<int>(s.size())};
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));

        // Base case
        // All diagonal elements should be 1
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        // All length 2 strings are palindromes if they are same alphabets
        // We also keep track of the max length of the palindrome and where it ends
        int max_length{1}, max_index{0};
        for (int i = 1; i < n; i++)
        {
            dp[i - 1][i] = s[i - 1] == s[i];
            if (dp[i - 1][i])
            {
                max_length = 2;
                max_index = i;
            }
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
                {
                    max_length = len;
                    max_index = i;
                }
            }

        // Get the substring ending at max_index(inclusive) of length max_value
        return s.substr(max_index + 1 - max_length, max_length);
    }

    /**
     * Space optimized bottom up 2D DP solution
     * by expanding around the centers
     *
     * Theta(n^2) time and Theta(1) space complexity
     */
    static std::string solution2(const std::string &s)
    {
        // Start at char at i and expand outwards to see if it is a palindrome
        // and if it is a palindrome
        // update the start and end positions of the largest palindrome
        int n{static_cast<int>(s.size())};
        int start{0}, max_length{0};
        for (int i = 0; i < n; i++)
        {
            // odd lengthed palindromes
            // we can start with palindromes of length 3
            // as 1 lengthed palindrome is already recorded
            // by initializing start = 0, max_length = 1 => first char is the initial
            // longest palindrome
            run_expanding_around_center(s, i - 1, i + 1, start, max_length);

            // even lengthed palindromes
            // We can start with palindromes of length 2
            run_expanding_around_center(s, i, i + 1, start, max_length);
        }

        // Get the substring starting at start and ending at end (inclusive)
        // Its length is end - start + 1
        return s.substr(start, max_length);
    }

    static void run_expanding_around_center(const std::string &s, int l, int r, int &start, int &max_length)
    {
        int n{static_cast<int>(s.size())};
        while (l >= 0 && r < n && s[l] == s[r])
        {
            // if length of current pallindrome (from l to r inclusive)
            // is greater than (from start to end inclusive)
            // update start and end
            if (r - l + 1 > max_length)
            {
                start = l;
                max_length = r;
            }
            l--;
            r++;
        }
    }

    /**
     * TODO: Manacher's algorithm
     * A linear time solution based on KMP algorithm
     */
    static std::string solution3(const std::string &s) { return ""; }

public:
    std::string longestPalindrome(std::string s) { return solution1(s); }
};