#include <string>
#include <vector>
#include <stack>

class Solution
{
private:
    static bool is_operator(std::string s) { return s == "+" || s == "-" || s == "*" || s == "/"; }
    static int compute(unsigned char op, int a, int b)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;

        // The default case will never be reached as the expression
        // and thereby operators are always valid
        default:
            return -1;
        }
    }

public:
    int evalRPN(std::vector<std::string> &tokens)
    {
        std::stack<int> stack;
        for (const auto &token : tokens)
        {
            if (is_operator(token))
            {
                // We can assume that there will be atleast 2 operands
                // as the given expression is a valid one
                int num1 = stack.top();
                stack.pop();
                int num2 = stack.top();
                stack.pop();

                stack.push(compute(token[0], num2, num1));
                continue;
            }

            // If it is not an operator, it is an operand
            // in which case we simply convert the token into a number
            // and add it to the stack
            stack.push(std::stoi(token));
        }

        return stack.top();
    }
};