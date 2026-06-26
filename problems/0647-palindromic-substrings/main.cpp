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
    std::string aug;

    void run_manachers()
    {
        int active_center = 0;
        int active_right_boundary = 0;

        for (int i = 0; i < aug_len; i++)
        {
            int i_mirror = 2 * active_center - i;

            int &curr_radius = radii[i];
            if (i < active_right_boundary)
                curr_radius = std::min(active_right_boundary - i, radii[i_mirror]);

            while (i - 1 - curr_radius >= 0 && i + 1 + curr_radius < aug_len &&
                   aug[i - 1 - curr_radius] == aug[i + 1 + curr_radius])
                curr_radius++;

            if (i + curr_radius > active_right_boundary)
            {
                active_center = i;
                active_right_boundary = i + curr_radius;
            }
        }
    }

public:
    Manachers(const std::string &input) : aug_len{2 * static_cast<int>(input.size()) + 1}, radii(aug_len)
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
     * Gets the total number of substrings contained within the given input string
     * Runs in Theta(n) time
     */
    unsigned long long get_num_palindromic_substrings() const
    {
        // If for a center the radius is 7, the length of the longest palindrome at
        // that center is 7 which means the number of palindromes (length 1, 3, 5, 7)
        // is (radius + 1) / 2
        // Works the same for even length radius as well, if the radius is 8,
        // the number of palindromes (length 2, 4, 6, 8) is (radius + 1) / 2
        // So the total number of palindromes
        // = ((radius[0] + 1)/2 + (radius[1] + 1)/2 + .. + (radius[aug_len-1] + 1)/2)
        // We can't simplify the above statement further as we need the floor of each of the terms
        // before adding
        return std::accumulate(radii.begin(), radii.end(), 0ULL, [](unsigned long long sum, int r)
                               { return sum + (r + 1) / 2; });
    }
};

class Solution
{
private:
    /**
     * Bottom up 2D DP solution
     * See problem 5 for more details
     *
     * Theta(n^2) time and space complexity
     */
    static int sol1(const std::string &s)
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
    static int sol2(const std::string &s)
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

    /**
     * Manacher's algorithm based solution
     * Theta(n) time and Theta(n) space
     */
    static int sol3(const std::string &s)
    {
        Manachers m(s);
        return m.get_num_palindromic_substrings();
    }

    /**
     * TODO: Palindromic Tree (EERTREE) based solution
     */
    static int sol4(const std::string &s) { return -1; }

public:
    int countSubstrings(const std::string &s) { return sol3(s); }
};