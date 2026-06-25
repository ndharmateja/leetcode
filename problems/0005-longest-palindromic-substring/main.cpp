#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

/**
 * Stripped down version of the full class
 * For full details, see the following reference:
 * ref: https://github.com/ndharmateja/data-structures-cpp/blob/master/algorithms/manachers/manachers.hpp
 */
class Manachers
{
    /**
     * Explanation:
     * Radius at center is defined the as the number of characters on each side
     * of the palindrome center in the augmented string
     * Eg: #I#A#I# with the center 'A' has radius 3 as there are 3 characters on each side
     * Eg: #I#I# with the center '#' has radius 2 as there are 2 characters on each side
     *
     * Notes:
     * 1. The index in the augmented string corresponding to original index 'i' is 2 * i + 1
     * 2. The radii vector will exactly capture the length of the palindrome
     *   centered at that index (for both even and odd lengthed substrings)
     *   Eg:
     *    original indices:    0     1     2     3     4     5     6     7     8     9     10    11
     *                         ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
     *        input string:    K     I     I     A     I     B     I     O     I     B     I     A
     *           augmented: #  K  #  I  #  I  #  A  #  I  #  B  #  I  #  O  #  I  #  B  #  I  #  A  #
     *               radii: 0  1  0  1  2  1  0  3  0  1  0  3  0  1  0  9  0  1  0  3  0  1  0  1  0
     *                      ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑
     *   augmented indices: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
     *   The longest palindrome centered at index 3 is IAI and the radius corresponding to
     *   its augmented center (index 7) is 3 (#I#A#I#)
     *   The longest palindrome centered between indices 1 and 2 is II and the radius corresponding
     *   to its augmented center (index 4) is 2 (#I#I#)
     */

private:
    static inline const char DELIMITER = '#';
    int aug_len;
    std::vector<int> radii;
    std::string str, aug;
    int longest_palindrome_len{0}, longest_palindrome_center{0};

    void run_manachers()
    {
        int active_center = 0;
        int active_right_boundary = 0;

        for (int i = 0; i < aug_len; i++)
        {
            // Find the mirror of the current index around the active center
            int i_mirror = 2 * active_center - i;

            int &curr_radius = radii[i];
            if (i < active_right_boundary)
                curr_radius = std::min(active_right_boundary - i, radii[i_mirror]);

            // Step 3: The Expansion Loop
            // This only actually iterates if we are in Case 3, or if 'i' is past 'R' entirely.
            while (i - 1 - curr_radius >= 0 && i + 1 + curr_radius < aug_len &&
                   aug[i - 1 - curr_radius] == aug[i + 1 + curr_radius])
                curr_radius++;

            // Update the max palindrome length
            // Note that the radius represents the palindrome length centered here
            // (read the explanation above for more details)
            if (curr_radius > longest_palindrome_len)
            {
                longest_palindrome_len = curr_radius;
                longest_palindrome_center = i;
            }

            // Step 4: The Handoff (Update the Active Center)
            // If this palindrome pushed the frontier further right, it dethrones the old center.
            if (i + curr_radius > active_right_boundary)
            {
                active_center = i;
                active_right_boundary = i + curr_radius;
            }
        }
    }

public:
    Manachers(const std::string &input) : aug_len{2 * static_cast<int>(input.size()) + 1}, radii(aug_len), str{input}
    {
        // Create the augmented string with the delimiter (default is #)
        // to be able to detect even lengthed palindromes
        aug.reserve(aug_len);
        aug.push_back(DELIMITER);
        for (unsigned char c : input)
        {
            aug.push_back(c);
            aug.push_back(DELIMITER);
        }

        // Run Manacher's algorithm which will update the radii vector
        run_manachers();
    }

    /**
     * Gets the longest palindrome contained within the given input string (returns the
     * leftmost one if there are ties)
     * Runs in Theta(1) time
     */
    std::string get_longest_palindrome() const
    {
        //           3     4     5     6     7     8     9     10    11
        //           ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
        // Eg:    #  A  #  I  #  B  #  I  #  O  #  I  #  B  #  I  #  A  #
        // radii: 1  3  0  1  0  3  0  1  0  9  0  1  0  3  0  1  0  1  0
        //        ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑
        //        6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
        // longest_palindrome_center is 15 and the start index in the string is (15-9)/2 = 3
        int start_index = (longest_palindrome_center - longest_palindrome_len) / 2;
        return str.substr(start_index, longest_palindrome_len);
    }
};

class Solution
{
private:
    /**
     * !Invalid solution
     * Doesn't work as we are not considering smaller lengths of palindromes that at end i-1
     * for forming a palindrome that ends at i
     * Eg: AAAA (fails for index 3)
     *
     * Bottom up DP solution
     * static std::string sol1(std::string s)
     * {
     *     * DP solution:
     *     dp[i]: length of the longest palindromic substring ending at index i in the string
     *     * Base case:
     *     dp[0] = 1
     *     * Recurrence relation:
     *     dp[i] = dp[i-1] + 2   if       (i-1) - dp[i-1] >= 0 and s[i] == s[(i-1) - dp[i-1]]
     *           = 3             else if  i - 2 >= 0           and s[i] == s[i-2]
     *           = 2             else if  s[i] == s[i-1]
     *           = 1             otherwise
     *     * Order of filling:
     *     from left to right as we only need the value on the left
     *     * Final answer:
     *     max_i = the index for which dp[i] is max
     *     max_length = dp[max_i]
     *     then the s[max_i + 1 - max_length: max_i + 1] is the longest palindromic substring
     *     int n{static_cast<int>(s.size())};
     *     std::vector<int> dp(n);
     *
     *     Base case:
     *     dp[0] = 1;
     *
     *     Fill the array from left to right
     *     int max_index{0}, max_length{1};
     *     for (int i = 1; i < n; i++)
     *     {
     *         int prev_value = dp[i - 1];
     *         if ((i - 1) - prev_value >= 0 && s[i] == s[(i - 1) - prev_value])
     *         dp[i] = prev_value + 2;
     *         else if (i - 2 >= 0 && s[i] == s[i - 2])
     *         dp[i] = 3;
     *         else if (s[i] == s[i - 1])
     *         dp[i] = 2;
     *         else
     *         dp[i] = 1;
     *
     *         Keep track of the max value and index in the dp array
     *         if (dp[i] > max_length)
     *         {
     *             max_length = dp[i];
     *             max_index = i;
     *         }
     *     }
     *
     *     Get the substring ending at max_index (inclusive) of length max_value
     *     return s.substr(max_index + 1 - max_length, max_length);
     * }
     */

    /**
     * Bottom up 2D DP solution
     *
     * Theta(n^2) time and space complexity
     */
    static std::string sol1(const std::string &s)
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
    static std::string sol2(const std::string &s)
    {
        // Start at char at i and expand outwards to see if it is a palindrome
        // and if it is a palindrome
        // update the start and max_length of the largest palindrome
        int n{static_cast<int>(s.size())};
        int start{0}, max_length{1};
        for (int i = 0; i < n; i++)
        {
            // odd lengthed palindromes
            // we can start with palindromes of length 3
            // as 1 lengthed palindrome is already recorded
            // by initializing start = 0, max_length = 1 => first char is the initial
            // longest palindrome
            run_expanding_around_center(s, n, i - 1, i + 1, start, max_length);

            // even lengthed palindromes
            // We can start with palindromes of length 2
            run_expanding_around_center(s, n, i, i + 1, start, max_length);
        }

        // Get the substring starting at start and ending at end (inclusive)
        // Its length is end - start + 1
        return s.substr(start, max_length);
    }

    static void run_expanding_around_center(const std::string &s, int n, int l, int r, int &start, int &max_length)
    {
        while (l >= 0 && r < n && s[l] == s[r])
        {
            // if length of current pallindrome (from l to r inclusive)
            // is greater than (from start to end inclusive)
            // update start and end
            if (r - l + 1 > max_length)
            {
                start = l;
                max_length = r - l + 1;
            }
            l--;
            r++;
        }
    }

    /**
     * Manacher's algorithm based solution
     * Theta(n) time and Theta(n) space
     */
    static std::string sol3(const std::string &s)
    {
        Manachers m(s);
        return m.get_longest_palindrome();
    }

public:
    std::string longestPalindrome(std::string s) { return sol3(s); }
};