#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution
{
private:
    /**
     * Sort the vector and see if any adjacent elements are the same
     * Theta(n lg n) time and Theta(lg n) space (for recursion in sorting)
     */
    static bool solution1(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        int n{static_cast<int>(nums.size())};
        for (int i = 0; i < n - 1; ++i)
            if (nums[i] == nums[i + 1])
                return true;

        // If we reach here, it means that there aren't any duplicates
        return false;
    }

    /**
     * Brute force solution: compare all possible pairs
     * Theta(n^2) time and Theta(1) space
     */
    static bool solution2(std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        for (int i = 0; i < n - 1; ++i)
            for (int j = i + 1; j < n; j++)
                if (nums[i] == nums[j])
                    return true;

        // If we reach here, it means that there aren't any duplicates
        return false;
    }

    /**
     * unordered set solution
     * Theta(n) time and Theta(n) space
     */
    static bool solution3(std::vector<int> &nums)
    {
        // We reserve the space for n elements in the set to avoid potential rehashes
        int n{static_cast<int>(nums.size())};
        std::unordered_set<int> set(n);
        for (auto num : nums)
        {
            // insert tries to insert it, and returns a pair of iterator to the element and
            // bool indicating whether insertion took place (false if already present).
            // This is better than count() and emplace() as two hashes are required
            auto result = set.insert(num);
            if (!result.second)
                return true;
        }

        // If we reach here, it means that there aren't any duplicates
        return false;
    }

public:
    bool containsDuplicate(std::vector<int> &nums) { return solution3(nums); }
};