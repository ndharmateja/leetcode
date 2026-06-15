#include <vector>

class Solution
{
private:
    /**
     * Finds all the subsets of the nums[idx:] and adds them to the result
     *
     * S  := the set of subsets that can be formed from nums[idx+1:]
     * S' := { x U {nums[idx]} for each x in S }
     *
     * S' is the set formed by adding nums[idx] to each of the elements of S
     * Then the subsets of nums[idx:] = S U S'
     * S can be found recursively
     *
     * Eg: nums = [A, B, C]
     * then S = subsets formed by nums[1:]
     *        = {{}, {B}, {C}, {B, C}}
     * then S' = (nums[idx]=nums[0]=A) added to each of the elements of S
     *         = {{A}, {A, B}, {A, C}, {A, B, C}}
     * subsets formed by nums = S U S'
     *                        = {{}, {B}, {C}, {B, C}, {A}, {A, B}, {A, C}, {A, B, C}}
     */
    static void backtrack(const std::vector<int> &nums, const int idx, const int n,
                          std::vector<std::vector<int>> &result)
    {
        // Base case:
        // when idx is n, then all the subsets formed by nums[n:] = {{}}
        // is just the set of empty set as the empty set is the only subset
        if (idx == n)
        {
            result.push_back(std::vector<int>());
            return;
        }

        // Collect all the subsets formed by nums[idx+1:] in the result
        backtrack(nums, idx + 1, n, result);

        // Add nums[idx] to each of the elements in the result
        // and add the new subsets
        // ! We can't do a for each loop as we are also modifying the result in the loop
        int result_size{static_cast<int>(result.size())};
        for (int i = 0; i < result_size; i++)
        {
            result.push_back(result[i]);
            result.back().push_back(nums[idx]);
        }
    };

    static std::vector<std::vector<int>> sol(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        std::vector<std::vector<int>> result;
        result.reserve(1 << n);
        backtrack(nums, 0, n, result);
        return result;
    };

public:
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums) { return sol(nums); };
};