#include <vector>
#include <string>
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
     * Returns if the substring in the range [start, end) is a palindrome
     * start is inclusive but end is exclusive
     */
    bool is_palindrome(int start, int end) const
    {
        // If start == end or start == end - 1
        // it means we are looking at 0 and 1 lengthed substrings
        // which will always be palindromes
        if (start == end || start == end - 1)
            return true;

        // [start, end-1] is the range we are looking for
        // corresponding indices in the augmented string = [2*start + 1, 2*(end-1) + 1]
        // Center in the augmented string
        // = [(2start + 1) + (2(end-1) + 1)] / 2 = start + (end-1) + 1 = start + end
        // int substr_len{end - start};
        // int center = {start + end};

        // The radius at this center tells us the length of the palindrome centered here
        // so if this length is greater than or equal to the substring length
        // then it is a palindrome
        // return radii[center] >= substr_len
        return radii[start + end] >= (end - start);
    }
};

class Solution
{
private:
    static void backtrack(const std::string &s, int idx, int n,
                          std::vector<std::string> &current_path,
                          std::vector<std::vector<std::string>> &result,
                          const Manachers &manachers)
    {
        if (idx == n)
        {
            result.push_back(current_path);
            return;
        }

        for (int j = idx + 1; j <= n; j++)
        {
            // If s[idx:j] is not a palindrome, then we don't need to backtrack
            if (!manachers.is_palindrome(idx, j))
                continue;

            // s[idx:j] is a palindrome, so we can add 'j' to the current_path
            // as j forms the (non-inclusive) end of this new palindrome
            current_path.push_back(s.substr(idx, j - idx));
            backtrack(s, j, n, current_path, result, manachers);
            current_path.pop_back();
        }
    }

public:
    /**
     * Same as solution 3 except the palindrome checking is done using
     * Manacher's algorithm
     */
    std::vector<std::vector<std::string>> partition(const std::string &s)
    {
        // Reserve the space for the current path (max size is n if all single letter
        // palindromes)
        int n{static_cast<int>(s.size())};
        std::vector<std::string> current_path;
        current_path.reserve(n);

        // Compute palindrome information for all pairs in Theta(n)
        Manachers manachers(s);

        // Create the result vector & backtrack & return the result
        std::vector<std::vector<std::string>> result;
        backtrack(s, 0, n, current_path, result, manachers);
        return result;
    }
};