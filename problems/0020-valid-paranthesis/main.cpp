#include <string>

class Solution
{
private:
    static constexpr bool is_opening(char c) { return c == '(' || c == '[' || c == '{'; }
    static constexpr bool is_matching(char opening, char closing)
    {
        return (opening == '(' && closing == ')') ||
               (opening == '[' && closing == ']') ||
               (opening == '{' && closing == '}');
    }

public:
    bool isValid(const std::string &s)
    {
        // Edge case:
        // If odd number of elements in the string, we can immediately return false
        int n{static_cast<int>(s.size())};
        if (n % 2 != 0)
            return false;

        // Use string as a stack for cache locality and small string optimization
        // The max number of characters a stack can have is n / 2 for a valid paranthesis string
        std::string stack;
        stack.reserve(n / 2);
        for (const char c : s)
        {
            // If it is an opening bracket, add it to the stack
            if (is_opening(c))
            {
                // ! Optimization: If the number of opening brackets on the stack
                // ! is already n/2, then we can immediately return false
                if (stack.size() == n / 2)
                    return false;

                stack.push_back(c);
                continue;
            }

            // If it is a closing bracket, pop the stack and see if it matches
            // According to leetcode constraints, we only have opening and closing brackets
            // so we don't need to check for other characters
            // So at this point we have a closing bracket
            // Normally, we would skip the other characters

            // If the stack is empty at this point, it means balancing is not valid
            // as there is no opening bracket corresponding to the closing
            if (stack.empty())
                return false;

            // See if the top most char on the stack is matching with the curr char
            char popped = stack.back();
            if (!is_matching(popped, c))
                return false;

            // Pop the opening bracket from the stack
            stack.pop_back();
        }

        // At this point, if the stack is empty it means it is balanced
        // because if it is not empty, it means that there are opening brackets
        // that aren't closed
        return stack.empty();
    }
};