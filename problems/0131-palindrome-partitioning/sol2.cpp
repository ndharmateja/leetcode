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
                                    std::vector<std::vector<bool>> &is_palindrome)
    {
        // Create a nxn DP array
        // is_palindrome[i][j] keeps track if s[i:j] is a palindrome (inclusive of i and j)
        int n{static_cast<int>(s.size())};

        // Base case
        // All diagonal elements should be 1
        for (int i = 0; i < n; i++)
            is_palindrome[i][i] = true;

        // All length 2 strings are palindromes if they are same alphabets
        // We also keep track of the max length of the palindrome and where it ends
        for (int i = 1; i < n; i++)
            is_palindrome[i - 1][i] = s[i - 1] == s[i];

        // Fill the table
        // in increasing order of string lengths
        for (int len = 3; len <= n; len++)
            for (int i = len - 1; i < n; i++)
                // We can check if s[i - (len-1): i] (inclusive) is a palindrome
                // by checking if is_palindrome[i - (len-1) + 1][i - 1] is true (which is checking
                // if the string after removing the first and last characters is a palindrome)
                // and checking if the first and last characters are the same
                is_palindrome[i - (len - 1)][i] = (s[i - (len - 1)] == s[i]) && is_palindrome[i - (len - 1) + 1][i - 1];
    }

    /**
     * Invariants:
     * 1. computed[idx] = false
     */
    static void backtrack(const std::string &s, int idx, int n,
                          std::vector<std::vector<std::vector<std::pair<int, int>>>> &memo,
                          std::vector<bool> &computed,
                          std::vector<std::vector<bool>> &is_palindrome)
    {
        // If s[idx:j] is a palindrome, then we can partition s[j:] into
        for (int j = idx + 1; j <= n; j++)
        {
            if (!is_palindrome[idx][j - 1])
                continue;

            // At this point, s[idx:j] is a palindrome, so we can partition
            // s[j:] into palindromes
            // Check if the palindrome partition of s[j:] is already computed
            // if not, we can compute it
            if (!computed[j])
                backtrack(s, j, n, memo, computed, is_palindrome);

            // Now we can add the substring s[idx:j] to each of the partitions of
            // s[j:] and add all these partitions to the result
            // Eg: if s[j:] is "aab"
            // memo[j] would be {{"a", "a", "b"}, {"aa", "b"}}
            std::vector<std::vector<std::pair<int, int>>> &idx_partition = memo[idx];
            for (const std::vector<std::pair<int, int>> &partition : memo[j])
            {
                idx_partition.push_back({{idx, j - idx}});
                idx_partition.back().insert(idx_partition.back().end(),
                                            partition.begin(), partition.end());
            }
        }
        computed[idx] = true;
    }

    static std::vector<std::vector<std::string>> sol(const std::string &s)
    {

        // Allocate space for exactly 'n' elements up front
        int n{static_cast<int>(s.size())};

        // Compute palindrome information for all pairs
        std::vector<std::vector<bool>> is_palindrome(n, std::vector<bool>(n));
        compute_palindromes(s, is_palindrome);

        // Initialize the memo including the base case
        std::vector<std::vector<std::vector<std::pair<int, int>>>> memo;
        memo.assign(n + 1, std::vector<std::vector<std::pair<int, int>>>());
        memo[n] = {{}};

        // Initialize the computed vector including the base case
        std::vector<bool> computed;
        computed.assign(n + 1, false);
        computed[n] = true;

        // Backtrack
        backtrack(s, 0, n, memo, computed, is_palindrome);

        // Construct the actual partitions from the indices
        // Eg: if s="aab", then result_indices will be {{{0, 1}, {1, 1}, {2, 1}}, {{0, 2}, {2, 1}}}
        //                            corresponding to {{   "a",    "a",    "b"}, {  "aa",    "b"}}
        const std::vector<std::vector<std::pair<int, int>>> &result_indices = memo[0];
        std::vector<std::vector<std::string>> result;
        result.reserve(result_indices.size());
        for (const std::vector<std::pair<int, int>> &partition : result_indices)
        {
            result.push_back({});
            for (const auto &[idx, len] : partition)
                result.back().push_back(s.substr(idx, len));
        }
        return result;
    }

public:
    std::vector<std::vector<std::string>> partition(const std::string &s) { return sol(s); }
};