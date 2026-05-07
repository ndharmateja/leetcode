#include <vector>
#include <queue>
#include <algorithm>

class Solution
{
private:
    /**
     * Max heap solution
     * Theta(n log n) time and Theta(n) space
     */
    static int solution1(const std::vector<int> &stones)
    {
        // Edge case: if only one stone, that is the answer
        if (stones.size() == 1)
            return stones.front();

        // Create a max heap and do the operations
        // Heapify runs in O(n)
        std::priority_queue<int, std::vector<int>, std::less<>> max_pq(stones.begin(), stones.end());
        while (max_pq.size() > 1)
        {
            // Extract the biggest two stones
            int stone1 = max_pq.top();
            max_pq.pop();
            int stone2 = max_pq.top();
            max_pq.pop();

            // If both stones have the same weight, they are destroyed
            // If one is bigger, then the difference is added a new stone
            if (stone1 > stone2)
                max_pq.push(stone1 - stone2);
        }

        // At this point if no stones are left, we return 0
        // else we return the weight of the one stone that is left
        return max_pq.empty() ? 0 : max_pq.top();
    }

public:
    int lastStoneWeight(const std::vector<int> &stones) { return solution1(stones); }
};