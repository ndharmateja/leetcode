#include <queue>
#include <algorithm>

/**
 * Invariant:
 * say n = #total elements
 *
 * If n is even, then max_pq contains the smallest n/2 elements
 * and the min_pq contains the largest n/2 elements
 * If n is odd, then max_pq contains the smallest ceiling(n/2) elements
 * and the min_pq contains the largest floor(n/2) elements
 * which means that max_pq would have one extra element
 *
 * We are using the max_pq for the smaller half and min_pq for the larger half
 * as we can very quickly get the largest among the smaller half and the smallest
 * element in the larger half to calculate the median
 * If n is even, the median is the average of max_pq.max() and min_pq.min()
 * If n is odd, the median is max_pq.max()
 */
namespace Solution1
{
    class MedianFinder
    {
    private:
        std::priority_queue<int, std::vector<int>, std::less<>> max_pq;
        std::priority_queue<int, std::vector<int>, std::greater<>> min_pq;

    public:
        /**
         * O(log n) time and Theta(1) space
         * Best case : 1 heap op (push)
         * Worst case: 3 heap ops (push, push, pop)
         * But multiple branches for branch predictor
         */
        void addNum(int num)
        {
            // If the max_pq is empty, it means that there are no elements so far
            // so we can directly add it to the max_pq
            if (max_pq.empty())
                max_pq.push(num);

            // If the max_pq is not empty and and the value <= largest value in
            // max_pq we can add it to the max_pq
            // Ideally we could add it to the max_pq if value <= smallest value
            // in the min_pq, but we need an extra edge case to check if the min_pq
            // is empty
            // So the values in the [-100000, max_pq.max()] we add it in the max_pq
            // and the values in the (max_pq.max(), min_pq.min()] (which could be added to the max_pq as well)
            // and (min_pq.min(), 100000] are added in the min_pq
            else if (num <= max_pq.top())
                max_pq.push(num);
            else
                min_pq.push(num);

            // Make it balanced
            // If both are same size or max_pq has one extra element, we don't need to do anything
            // If max_pq has more than one element extra, we move one element from max_pq to min_pq
            // !Be careful of integer overflows and not use subtractions as sizes are unsigned
            if (max_pq.size() > min_pq.size() + 1)
            {
                min_pq.push(max_pq.top());
                max_pq.pop();
                return;
            }

            // Similarly we do the reverse if min_pq has more elements than max_pq
            // as the invariant is either same # of elements in both pqs
            // or max_pq can have one extra element
            if (min_pq.size() > max_pq.size())
            {
                max_pq.push(min_pq.top());
                min_pq.pop();
                return;
            }
        }

        /**
         * Theta(1) time
         */
        double findMedian()
        {
            // As the invariant is that the smallest half elements are in the max_pq
            // (with potentially one extra) and the largest half elements are in the
            // min_pq, the median is going to be the average of max_pq.max() and min_pq.min()
            // if same # of elements or max_pq.max() if the max_pq has one extra element
            if (max_pq.size() == min_pq.size())
                return (max_pq.top() + min_pq.top()) / 2.0;
            return max_pq.top();
        }
    };
}

/**
 * Same as Solution1 but with a cleaner addNum() method
 * Read Solution1 first
 */
namespace Solution2
{
    class MedianFinder
    {
    private:
        std::priority_queue<int, std::vector<int>, std::less<>> max_pq;
        std::priority_queue<int, std::vector<int>, std::greater<>> min_pq;

    public:
        /**
         * Self correcting strategy
         * O(log n) time and Theta(1) space
         * Best case : 3 heap ops (push, push, pop)
         * Worst case: 5 heap ops (push, push, pop, push, pop)
         * But cleaner code and fewer branches
         */
        void addNum(int num)
        {
            // Add the element directly to the max_pq
            max_pq.push(num);

            // It could be possible that we added an element that is larger than
            // min_pq.min() into the max_pq
            // So we can blindly move max element from max_pq to min_pq
            // This fixes the above issue when we push an element > min_pq.min()
            // into the max_pq
            // But also doesn't cause any issue even if element <= min_pq.min()
            // We don't need an edge case as atleast one element in max_pq as we just pushed
            min_pq.push(max_pq.top());
            max_pq.pop();

            // If the pqs were having the same size before, then the above two operations
            // will make the min_pq have the extra element. So reset the invariant.
            if (min_pq.size() > max_pq.size())
            {
                max_pq.push(min_pq.top());
                min_pq.pop();
            }
        }

        /**
         * Theta(1) time
         */
        double findMedian()
        {
            // As the invariant is that the smallest half elements are in the max_pq
            // (with potentially one extra) and the largest half elements are in the
            // min_pq, the median is going to be the average of max_pq.max() and min_pq.min()
            // if same # of elements or max_pq.max() if the max_pq has one extra element
            if (max_pq.size() == min_pq.size())
                return (max_pq.top() + min_pq.top()) / 2.0;
            return max_pq.top();
        }
    };
}