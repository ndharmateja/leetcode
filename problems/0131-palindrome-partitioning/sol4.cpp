#include <vector>
#include <string>

class Solution
{
private:
    static void backtrack(const std::string &s, int idx, int n,
                          const std::vector<char> &is_palindrome,
                          std::vector<std::string> &current_path,
                          std::vector<std::vector<std::string>> &result)
    {
    }

public:
    /**
     * TODO: 1. Manacher's algo based solution
     * It can tell if a substring is a palindrome in constant time
     * TODO: 2. Store just the ending index of each substring instead of pair (idx, len)
     * We can find the start of palindrome substring based on the end of the prev palindrome
     * TODO: 3. Remove memoization
     */
    std::vector<std::vector<std::string>> partition(const std::string &s) {}
};