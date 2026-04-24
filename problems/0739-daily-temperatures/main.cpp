#include <vector>
#include <stack>

class Solution
{
public:
    /**
     * Theta(n) time in any case (as each item gets pushed exactly once and popped atmost once)
     * Theta(n) space complexity in the worst case (when all temperatures are non-increasing)
     * Theta(1) space complexity in the best case (when all temperatures are increasing)
     */
    std::vector<int> dailyTemperatures(const std::vector<int> &temperatures)
    {
        // We store a stack of indices of non decreasing temperatures
        // Every time we encounter a new value, we can remove all the values on the stack
        // that have a smaller temperature and updating its result which is the difference
        // of the new temperature and the index stored in the stack
        int n{static_cast<int>(temperatures.size())};
        std::stack<int> stack;
        std::vector<int> result(n);

        for (int i = 0; i < n; i++)
        {
            // Remove all the indices of temperatures from the stack that are smaller than the
            // current temperature and update its result
            int curr_temperature = temperatures[i];
            while (!stack.empty())
            {
                // If the temperature at the top of the stack is >= current temperature
                // it means that the current temperature is <= all the temperatures in
                // the stack
                // So this can't be the warmer temperature. So we add this to the stack.
                int old_index = stack.top();
                int old_temperature = temperatures[old_index];
                if (old_temperature >= curr_temperature)
                    break;

                // At this point, the current temperature > the top temperature
                // so this is the first warmer day than the top temperature
                // and the number of days to wait is exactly the difference in the
                // indices. So we can remove the top value from the stack and update its result.
                stack.pop();
                result[old_index] = i - old_index;
            }

            // Add the current temperature and the index to the stack
            stack.push(i);
        }

        // At this point, all the elements in the stack didn't encounter a warmer temperature
        // but we don't need to explicitly set all those indices to 0 because in c++
        // vector(n) initializes the values to 0s

        // Return the result
        return result;
    }
};