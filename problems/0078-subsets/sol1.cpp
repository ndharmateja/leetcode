#include <vector>

class Solution
{
private:
    /**
     * There is a bijection (one to one mapping) between unique subsets and unique subsequences
     * Eg: If nums = {A, B, C}
     * then subset {C, A} is equivalent to the subsequence {A, C}
     *
     * Finding all the subsets is equivalent to finding all the subsequences
     *
     * This function recursively extends the buffer with each of the
     * possible subsequences that can be formed using only elements from nums[min_index:]
     * and adds them all to the result
     *
     * Eg: nums = {A, B, C}
     * If we call backtrack(buffer={A}, min_index=1)
     * All the subsequences that can be formed from nums[min_index:] = nums[1:]
     * are {B}, {B, C}, {C}, {}
     * The function will extend the buffer with each of those and add them to the result
     * so the result gets added with {A, B}, {A, B, C}, {A, C}, {A}
     *
     * Refer to the tree in sol1.png for more details
     */
    static void backtrack(const std::vector<int> &nums, int n,
                          std::vector<std::vector<int>> &result,
                          std::vector<int> &buffer, int min_index)
    {
        // Add the buffer to the result
        // Every node in the tree is a valid subset
        result.push_back(buffer);

        // If min_index reaches n, then there are no more elements to
        // go over, so we can exit
        // ! This is not strictly not necessary as the for loop won't be entered
        // ! when min_index == n
        // ! if (min_index == n)
        // !     return;

        // We need to find all the subsequences that can be formed using
        // nums[min_index:]
        // Each element nums[i] (min_index <= i < n) can be picked as the first
        // element of the subsequence
        // So we add it to the buffer and recursively explore everything
        // from nums[i+1:] as we only want subsequences
        for (int i = min_index; i < n; i++)
        {
            buffer.push_back(nums[i]);
            backtrack(nums, n, result, buffer, i + 1);
            buffer.pop_back();
        }
    }

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums)
    {
        // Create the vectors for the buffer (max size n) and the result
        // which will have 2^n elements at the end
        // Reserve the sizes for both these vectors to prevent reallocations
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        std::vector<int> buffer;
        result.reserve(1 << n);
        buffer.reserve(n);

        // Backtrack and return the result
        backtrack(nums, n, result, buffer, 0);
        return result;
    };

public:
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums) { return sol(nums); };
};