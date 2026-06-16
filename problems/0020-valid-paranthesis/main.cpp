#include <string>
#include <stack>

class Solution
{
private:
    static inline bool is_opening(char c) { return c == '(' || c == '[' || c == '{'; }
    static inline bool is_closing(char c) { return c == ')' || c == ']' || c == '}'; }
    static inline bool is_matching(char opening, char closing)
    {
        return (opening == '(' && closing == ')') ||
               (opening == '[' && closing == ']') ||
               (opening == '{' && closing == '}');
    }

public:
    bool isValid(std::string s)
    {
        std::stack<char> stack;
        for (unsigned char c : s)
        {
            // If it is an opening bracket, add it to the stack
            if (is_opening(c))
            {
                stack.push(c);
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
            char popped = stack.top();
            if (!is_matching(popped, c))
                return false;

            // Pop the opening bracket from the stack
            stack.pop();
        }

        // At this point, if the stack is empty it means it is balanced
        // because if it is not empty, it means that there are opening brackets
        // that aren't closed
        return stack.empty();
    }
};