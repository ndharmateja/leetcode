#include <string>
#include <vector>

class Solution
{
public:
    static bool is_palindrome(const std::string &s, int start, int end)
    {
        while (start < end)
            if (s[start++] != s[end--])
                return false;
        return true;
    }

    /**
     * Invariants:
     * 1. computed[idx] = false
     */
    static void backtrack(const std::string &s, int idx, int n,
                          std::vector<std::vector<std::vector<std::string>>> &memo,
                          std::vector<bool> &computed)
    {
        // If s[idx:j] is a palindrome, then we can partition s[j:] into
        for (int j = idx + 1; j <= n; j++)
        {
            if (!is_palindrome(s, idx, j - 1))
                continue;

            // At this point, s[idx:j] is a palindrome, so we can partition
            // s[j:] into palindromes
            // Check if the palindrome partition of s[j:] is already computed
            // if not, we can compute it
            if (!computed[j])
                backtrack(s, j, n, memo, computed);

            // Now we can add the substring s[idx:j] to each of the partitions of
            // s[j:] and add all these partitions to the result
            // Eg: if s[j:] is "aab"
            // memo[j] would be {{"a", "a", "b"}, {"aa", "b"}}
            std::vector<std::vector<std::string>> &idx_partition = memo[idx];
            std::string curr_palindrome = s.substr(idx, j - idx);
            for (const std::vector<std::string> &partition : memo[j])
            {
                idx_partition.push_back({curr_palindrome});
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

        // Initialize the memo including the base case
        std::vector<std::vector<std::vector<std::string>>> memo;
        memo.assign(n + 1, std::vector<std::vector<std::string>>());
        memo[n] = {{}};

        // Initialize the computed vector including the base case
        std::vector<bool> computed;
        computed.assign(n + 1, false);
        computed[n] = true;

        // Backtrack
        backtrack(s, 0, n, memo, computed);
        return memo[0];
    }

public:
    std::vector<std::vector<std::string>> partition(const std::string &s) { return sol(s); }
};