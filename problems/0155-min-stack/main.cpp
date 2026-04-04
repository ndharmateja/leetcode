#include <stack>
#include <utility>
#include <algorithm>

/**
 * Min stack is implemented by storing pairs of values (actual value & min so far)
 * on the stack instead of just the values.
 */
namespace Solution1
{
    class MinStack
    {
    private:
        std::stack<std::pair<int, int>> stack;

    public:
        void push(int val) { stack.push({val, stack.empty() ? val : std::min(val, stack.top().second)}); }

        // Leetcode constraints: pop and top will only be called on non-empty stacks
        // So error handling not required
        void pop() { stack.pop(); }
        int top() { return stack.top().first; }

        int getMin() { return stack.top().second; }
    };
}

/**
 * This no extra space solution works whenever there are no integer overflows
 * This doesn't work for the leetcode submission without having to change
 * the stack<int> to stack<long long> in which case it takes the same amount
 * of space as solution 1 (stack<pair<int, int>>).
 *
 * The above solution is also better because of lesser if-checks and computations
 * for each operation of push/pop/top
 *
 * Idea of this solution:
 * - When a new value is smaller than the min_so_far, we need to update it
 * but we would lose the old min_so_far. so we encode it in the value we
 * actually insert whenever the inserted value < min_so_far.
 * - We insert 2 * value - prev_min into the stack and make min_so_far as the value inserted.
 * We use 2 * value - prev_min because 2 * value - prev_min is less than value,
 * so that is the indication that min_so_far has been modified.
 * - proof: value < prev_min => value - prev_min < 0 => 2 * value - prev_min < value
 * - So while popping item of the stack, if the top value is smaller than the min_so_far,
 * it means that min_so_far was modified during the insertion. So we restore the old min
 * value.
 * inserted_value = 2 * actual_value - prev_min => prev_min = 2 * actual_value - inserted_value
 * and the actual_value was stored in the min_so_far
 * so prev_min = 2 * min_so_far - stack.top()
 */
namespace Solution2
{
    class MinStack
    {
    private:
        std::stack<int> stack;
        int min_so_far;

    public:
        void push(int val)
        {
            // If the stack is empty, then the min_so_far becomes the value itself
            if (stack.empty())
            {
                this->stack.push(val);
                this->min_so_far = val;
                return;
            }

            // At this point, we know that stack isn't empty
            // Our insertion depends upon whether the val is less than the min_so_far or not
            // If the val >= min_so_far, then we don't need to update the min_so_far
            if (val >= min_so_far)
            {
                this->stack.push(val);
                return;
            }

            // val < min_so_far
            // So we insert 2*val - min_so_far into the stack
            // and make the min_so_far = val
            // 2 * val - min_so_far = val - min_so_far + val (for integer overflow issues)
            this->stack.push(val - min_so_far + val);
            this->min_so_far = val;
        }

        // Leetcode constraints: pop and top will only be called on non-empty stacks
        // So error handling not required
        void pop()
        {
            // If the top most value in the stack is >= min_so_far, it means that the
            // min_so_far wasn't updated, we can simply pop and we don't need to update
            // the min_so_far
            int top_value = this->stack.top();
            if (top_value >= min_so_far)
            {
                this->stack.pop();
                return;
            }

            // But if the top most value < min_so_far, it means that the
            // min_so_far was updated to be the actual value
            // prev_min_so_far = 2 * min_so_far - top_value
            // 2 * min_so_far - top_value = min_so_far - top_value + min_so_far (for integer
            // overflow issues)
            this->stack.pop();
            this->min_so_far = this->min_so_far - top_value + this->min_so_far;
        }
        int top()
        {
            // If the top most value in the stack is >= min_so_far, it means that the
            // min_so_far wasn't updated, so the top value itself is the answer
            // But if the top most value < min_so_far, it means that the
            // min_so_far was updated to be the actual value
            int top_value = this->stack.top();
            return top_value >= this->min_so_far ? top_value : this->min_so_far;
        }

        // Min value so far is always in min_so_far
        int getMin() { return min_so_far; }
    };
}