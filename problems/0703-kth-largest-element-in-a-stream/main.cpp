#include <vector>
#include <queue>

class KthLargest
{
private:
    // We can store the k largest elements in a min heap
    // Using std::greater<> makes it a min heap
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    int k;

public:
    KthLargest(int k, std::vector<int> &nums) : k{k}
    {
        // Add all the nums to the pq, so that the size of the pq
        // never crosses 'k'
        // To save the overhead 
        for (const auto &num : nums)
            this->add(num);
    }

    int add(int val)
    {
        // Since k <= nums.length + 1 and nums.length can be 0 and k be 1
        // after the constructor, pq can be empty
        // So instead of optimizing it to add only when the val > currmin in heap
        // we unconditionally add the value and pop if size crosses k to maintain
        // the heap at k elements always
        this->pq.push(val);

        // If the size crosses k, remove the min
        if (this->pq.size() > k)
            this->pq.pop();

        // Return the kth largest element which is the min in the heap (if
        // there are k elements in the heap)
        return this->pq.top();
    }
};