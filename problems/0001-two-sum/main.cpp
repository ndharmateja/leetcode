#include <vector>
#include <unordered_map>

class Solution
{
private:
    /**
     * Hash map solution to find the numbers that add up to target.
     * Theta(N) worst case running time and Theta(n) worst case space complexity
     */
    static std::vector<int> solution1(std::vector<int> &nums, int target)
    {
        // Map that stores each number to its index
        int n{static_cast<int>(nums.size())};
        std::unordered_map<int, int> map(n);

        // Go over each element and find its complementary number
        for (int i = 0; i < n; i++)
        {
            // If target-num exists in the map already, they add up to target
            int num = nums[i];

            // Note: We have to first check and then add, as num=3 and target=6
            // would find 3 itself if we lookup first

            // If the complementary number exists, we return the index of that number
            // and the index of the current number
            auto it = map.find(target - num);
            if (it != map.end())
                return {it->second, i};

            // If the complementary number doesn't exist in the map,
            // we add the current number and index to the map
            map[num] = i;
        }

        // This would never be reached as a solution always exists
        return {};
    }

    /**
     * Brute force solution
     * Search all possible pairs.
     * Theta(n^2) worst case time and Theta(1) space
     */
    static std::vector<int> solution2(std::vector<int> &nums, int target)
    {
        int n{static_cast<int>(nums.size())};
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (nums[i] + nums[j] == target)
                    return {i, j};

        // This would never be reached as a solution always exists
        return {};
    }

public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) { return solution1(nums, target); }
};