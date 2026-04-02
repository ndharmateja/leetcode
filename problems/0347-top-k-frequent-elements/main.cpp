#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>

class Solution
{
private:
    /**
     * Theta(n) time and Theta(n) space solution
     */
    static std::vector<int> solution1(std::vector<int> &nums, int k)
    {
        // Get the counts of each number
        std::unordered_map<int, int> counts(nums.size());
        int max_count{0};
        for (const auto &num : nums)
        {
            // try_emplace is better than counts[num]++ (which also works)
            // because it will have to do a double hash lookup during the first insert
            // try_emplace will insert the key-value pair only if the key doesn't
            // already exist and if key already exists, it doesn't do anything
            auto [it, inserted] = counts.try_emplace(num, 0);
            it->second++;

            // Update the max count
            max_count = std::max(max_count, it->second);
        }

        // Create an array of vectors, where each index will hold the elements
        // having the count as that index
        std::vector<std::vector<int>> buckets(max_count + 1);
        for (const auto &[num, count] : counts)
            buckets[count].push_back(num);

        // Iterate from the end and collect k elements
        std::vector<int> result;
        for (int i = max_count; i >= 1; i--)
        {
            // If there are no elements in the current bucket, we skip it
            if (buckets[i].empty())
                continue;

            // Add the elements from the current index to the result
            result.insert(result.end(), buckets[i].begin(), buckets[i].end());

            // If the number of elements in the result is >= k we can break
            // Since we know that there is a unique solution, we can be sure that
            // the size would exactly be 'k'
            // so we don't need to resize
            if (result.size() >= k)
                // result.resize(k);
                return result;
        }

        // We would never reach here as we know that a valid solution exists
        return {};
    }

public:
    std::vector<int> topKFrequent(std::vector<int> &nums, int k) { return solution1(nums, k); }
};