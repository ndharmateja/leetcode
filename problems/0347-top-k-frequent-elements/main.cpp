#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>

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

    /**
     * Min heap solution, keep track of the top-k elements
     * Theta(n log k) time and Theta(n) space
     */
    static std::vector<int> solution2(std::vector<int> &nums, int k)
    {
        // Get the counts of each number
        std::unordered_map<int, int> counts(nums.size());
        for (const auto &num : nums)
        {
            // try_emplace is better than counts[num]++ (which also works)
            // because it will have to do a double hash lookup during the first insert
            // try_emplace will insert the key-value pair only if the key doesn't
            // already exist and if key already exists, it doesn't do anything
            auto [it, inserted] = counts.try_emplace(num, 0);
            it->second++;
        }

        // Create a min heap that holds only k elements at any point
        // std::greater<> works because the pair class has comparison built into it
        // but the comparison happens based on the first values, so we need to
        // put the count as the first value of the pair
        // std::greater<> should be used for min heap
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> min_heap;
        for (const auto &[num, count] : counts)
        {
            // Insert the pair of {count, num} in the min heap
            // count should be the first value as we are comparing pairs directly
            // and the comparison is based on the first values
            min_heap.push({count, num});

            // If the number of elements in heap cross k, we remove the min
            if (min_heap.size() > k)
                min_heap.pop();
        }

        // At this point we have the top k elements in the min heap
        // We can collect all the k numbers (the second values of the pair objects)
        // Better to create a k sized vector directly and then assign elements
        // instead of creating an empty list and then pushing elements due to resizing
        std::vector<int> result(k);
        for (size_t i = 0; i < k; i++)
        {
            result[i] = min_heap.top().second;
            min_heap.pop();
        }
        return result;
    }

public:
    std::vector<int> topKFrequent(std::vector<int> &nums, int k) { return solution2(nums, k); }
};