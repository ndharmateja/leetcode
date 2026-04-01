#include <stack>
#include <utility>

class MinStack
{
private:
    std::stack<std::pair<int, int>> stack;
    static int min(int a, int b) { return a <= b ? a : b; }

public:
    void push(int val) { stack.push({val, stack.empty() ? val : min(val, stack.top().second)}); }

    // Leetcode constraints: pop and top will only be called on non-empty stacks
    // So error handling not required
    void pop() { stack.pop(); }
    int top() { return stack.top().first; }

    int getMin() { return stack.top().second; }
};