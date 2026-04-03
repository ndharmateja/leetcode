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
        for (const auto &num : nums)
            this->add(num);
    }

    int add(int val)
    {
        this->pq.push(val);

        // If there are more than k elements, we remove the min
        if (pq.size() > k)
            this->pq.pop();

        // Return the kth largest element which is the min in the heap (if
        // there are k elements in the heap)
        return this->pq.top();
    }
};