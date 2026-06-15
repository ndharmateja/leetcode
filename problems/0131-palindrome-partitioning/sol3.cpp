#include <vector>
#include <string>

class Solution
{
private:
    /**
     * Bottom up 2D DP solution
     * See problem 647 for more details
     */
    static void compute_palindromes(const std::string &s,
                                    std::vector<char> &is_palindrome)
    {
        // Create a nxn DP array
        // is_palindrome[i][j] keeps track if s[i:j] is a palindrome (inclusive of i and j)
        int n{static_cast<int>(s.size())};

        // Base case
        // All diagonal elements should be 1
        for (int i = 0; i < n; i++)
            is_palindrome[i * n + i] = true;

        // All length 2 strings are palindromes if they are same alphabets
        // We also keep track of the max length of the palindrome and where it ends
        for (int i = 1; i < n; i++)
            is_palindrome[(i - 1) * n + i] = s[i - 1] == s[i];

        // Fill the table
        // in increasing order of string lengths
        for (int len = 3; len <= n; len++)
            for (int i = len - 1; i < n; i++)
            {
                // We can check if s[i - (len-1): i] (inclusive) is a palindrome
                // by checking if is_palindrome[i - (len-1) + 1][i - 1] is true (which is checking
                // if the string after removing the first and last characters is a palindrome)
                // and checking if the first and last characters are the same
                int row_idx{i - (len - 1)};
                is_palindrome[row_idx * n + i] = (s[row_idx] == s[i]) &&
                                                 is_palindrome[(row_idx + 1) * n + (i - 1)];
            }
    }

    static void backtrack(const std::string &s, int idx, int n,
                          const std::vector<char> &is_palindrome,
                          std::vector<std::string> &current_path,
                          std::vector<std::vector<std::string>> &result)
    {
        if (idx == n)
        {
            result.push_back(current_path);
            return;
        }

        // ! Optimization:
        // ! is_palindrome[idx][j-1] = is_palindrome[idx * n + (j-1)]
        // ! To prevent multiplication every loop, we can compute it outside
        // ! the loop and increment it
        // ! For the first iteration, j = idx + 1 => idx * n + (j - 1) = idx * (n + 1)
        int palindrome_index = idx * (n + 1);
        for (int j = idx + 1; j <= n; j++)
        {
            // If s[idx:j] is not a palindrome, then we don't need to backtrack
            if (!is_palindrome[palindrome_index++])
                continue;

            // s[idx:j] is a palindrome, so we can add 'j' to the current_path
            // as j forms the (non-inclusive) end of this new palindrome
            current_path.push_back(s.substr(idx, j - idx));
            backtrack(s, j, n, is_palindrome, current_path, result);
            current_path.pop_back();
        }
    }

public:
    /**
     * Improvements:
     * 1. No memoization
     * 2. Storing just the ends of the palindromes in a partition (and current path)
     *   (removed this optimization as this was consistently giving slower speeds
     *   probably due to small string optimization)
     * 3. 1D flattening of the is_palindrome 2D array
     * 4. vector<char> instead of vector<bool>
     * 5. Instead of multiplying everytime for 2D to 1D flattening, compute product
     *   outside the loop and increment the row major index (inside backtrack())
     */
    std::vector<std::vector<std::string>> partition(const std::string &s)
    {
        // Reserve the space for the current path (max size is n if all single letter
        // palindromes)
        int n{static_cast<int>(s.size())};
        std::vector<std::string> current_path;
        current_path.reserve(n);

        // Compute palindrome information for all pairs
        std::vector<char> is_palindrome(n * n);
        compute_palindromes(s, is_palindrome);

        // Create the result vector & backtrack & return the result
        std::vector<std::vector<std::string>> result;
        backtrack(s, 0, n, is_palindrome, current_path, result);
        return result;
    }
};