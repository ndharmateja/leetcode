#include <vector>
#include <queue>

class Solution
{
private:
    /**
     * Max heap solution
     *
     * Theta(n log k) time and Theta(k) space (for the heap)
     */
    std::vector<std::vector<int>> sol1(const std::vector<std::vector<int>> &points, const unsigned k)
    {
        /**
         * Explanation
         * 1. Create pairs of distances and their indices so that we can keep adding them
         *    in a max heap of max size k so that we are left with the k closest points in the end
         * 2. We store {distance, index} as the pair as when 2 pairs are compared,
         *    they are compared based on the 'first' field which is the distance first
         *    and then by the 'second' field
         * 3. We don't need to explicitly create a vector of pairs first as we can create and add them
         *    on the fly as won't need the Theta(n) space for the vector and we only need one pass.
         * 4. We also don't need the sqrt of distance as we only need relative ordering.
         */

        // Create the max heap and add the distances maintaining a max size of k for the maxheap
        int n{static_cast<int>(points.size())}, x, y, dist;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> max_heap;
        for (int idx{0}; idx < n; idx++)
        {
            // Add the distance and the index of the current point
            const auto &point = points[idx];
            x = point.front(), y = point.back();
            dist = (x * x) + (y * y);
            max_heap.push({dist, idx});

            // If the heap's size crosses k and becomes k+1, we can pop the max element
            // to still keep the k smallest distances so far
            if (max_heap.size() > k)
                max_heap.pop();
        }

        // Now we have the distances and the indices of the k closest points
        // which we can use to build our result
        std::vector<std::vector<int>> result;
        result.reserve(k);
        while (!max_heap.empty())
        {
            result.push_back(points[max_heap.top().second]);
            max_heap.pop();
        }
        return result;
    };

    /**
     * Quick select implementation.
     * For a custom quick select implementation, see problem 215.
     *
     * Theta(n) time (on average) and Theta(1) space
     */
    std::vector<std::vector<int>> sol2(std::vector<std::vector<int>> &points, int k)
    {
        /**
         * Explanation
         * We don't need to select each of the smallest elements k times. We can
         * select the 'k'th smallest element so that all the elements on the left
         * are "smaller" (closer to origin) than the selected element (not necessarily
         * in sorted order) due to the partition which is exactly what we want.
         */

        // Comparator for distances
        // We don't have to do square root as we only need the relative distances
        // from the origin
        auto dist_cmp = [](const std::vector<int> &p1, const std::vector<int> &p2)
        { return (p1[0] * p1[0] + p1[1] * p1[1]) < (p2[0] * p2[0] + p2[1] * p2[1]); };

        // Run quick select with 'k-1'
        // So that the 'k-1'th (0-indexed) smallest element goes at index k-1
        // and all the smaller elements go to its left (technically elements on the
        // left will be <= k-1'th element but we are guaranteed a unique solution
        // according to leetcode)
        // so that the first k elements will be the k smallest overall
        // Say k = 3
        // So if we run quick select with k-1=2, points[2] will have the 2nd smallest
        // and points[0] and points[1] will be smaller than points[2]
        // so points[0], points[1] and points[2] will form the smallest 3 elements
        std::nth_element(points.begin(), points.begin() + (k - 1), points.end(), dist_cmp);

        // The smallest k elements after running quick select with k
        // would be the k smallest elements overall (not necessarily sorted)
        // due to partitioning in quick select
        // So we can create a new vector with the smallest k elements after quick select
        return std::vector<std::vector<int>>(points.begin(), points.begin() + k);
    }

public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &points, int k) { return sol2(points, k); };
};