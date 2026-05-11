#include <string>
#include <vector>

class Solution
{
private:
    /**
     * Recursive function (memoized) that computes the #ways we can decode s[i:]
     */
    static int sol1(const std::string &s, int i, int n, std::vector<int> &memo)
    {
        // Edge case
        // If string starts with 0, then 0 ways
        if (s[i] == '0')
            return 0;

        // Base case
        // If index out of bounds, we can return 0
        if (i == n)
            return 1;

        // If memo contains the answer we can directly return it
        int &answer = memo[i];
        if (answer != -1)
            return answer;

        // We can try to form a number with just s[i] or s[i:i+2]
        // At this point we know that s[i] is non zero
        // So we can form a number with s[i]
        answer = sol1(s, i + 1, n, memo);

        // We can form a number with s[i:i+2] if there are two digits and
        // it forms a number between 10 and 26
        if (i <= n - 2 &&
            ((s[i] == '1') ||
             (s[i] == '2' && '0' <= s[i + 1] && s[i + 1] <= '6')))
            answer += sol1(s, i + 2, n, memo);

        // Return the answer
        return answer;
    }

    /**
     * Top down DP approach
     */
    static int sol1(const std::string &s)
    {
        int n{static_cast<int>(s.size())};
        std::vector<int> memo(n, -1);
        return sol1(s, 0, n, memo);
    }

public:
    int numDecodings(const std::string &s) { return sol1(s); }
};