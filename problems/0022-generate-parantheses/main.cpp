#include <vector>
#include <string>

class Solution
{
private:
    static void backtrack(int n, int num_opening, int num_closing,
                          std::vector<std::string> &result, std::string &buffer)
    {
        if (num_opening == n && num_closing == n)
        {
            result.push_back(buffer);
            return;
        }

        if (num_opening < n)
        {
            buffer.push_back('(');
            backtrack(n, num_opening + 1, num_closing, result, buffer);
            buffer.pop_back();
        }

        if (num_closing < num_opening)
        {
            buffer.push_back(')');
            backtrack(n, num_opening, num_closing + 1, result, buffer);
            buffer.pop_back();
        }
    }

    static std::vector<std::string> sol1(int n)
    {
        std::vector<std::string> result;
        std::string buffer;
        buffer.reserve(2 * n);
        backtrack(n, 0, 0, result, buffer);
        return result;
    }

public:
    std::vector<std::string> generateParenthesis(int n) { return sol1(n); }
};