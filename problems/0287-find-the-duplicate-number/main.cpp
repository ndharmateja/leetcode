#include <vector>
#include <unordered_set>

class Solution
{
private:
    /**
     * Uses the Floyd's algorithm to find the starting point
     * of the cycle. See method.jpeg to know why this problem maps
     * to the finding the cycle starting point of the linked list.
     *
     * The cycle has to be accessible from the index 0 as if we keep following
     * the indices, we keep going forever (because all the values in the vector are in [1, n])
     * in a finite list
     *
     * Ref: https://youtu.be/wjYnzkAhcNk
     *
     * Theta(N) time and Theta(1) space solution
     */
    static int solution1(const std::vector<int> &nums)
    {
        // Floyd's algorithm
        // Advance the slow pointer once and the fast pointer twice
        // until they meet
        int slow{0}, fast{0};
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Once them, we can start two pointers in unison (moving one step each)
        // one starting from the head, and the other from the meeting point
        // their new meeting point is the start of the cycle
        // We are reusing the fast pointer as the second slow pointer that
        // starts from the head of the linked list
        fast = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        // Once they meet, that is the start of the cycle
        return slow;
    }

    /**
     * Using an unordered set
     * Theta(N) time and Theta(N) space solution
     */
    static int solution2(const std::vector<int> &nums)
    {
        std::unordered_set<int> set(nums.size());
        for (int num : nums)
        {
            // This code does double hashing
            // if (set.count(num))
            //     return num;
            // set.emplace(num);

            // We can get away with a single hash
            auto [it, is_inserted] = set.insert(num);
            if (!is_inserted)
                return num;
        }

        // We would never reach here as the constraints of the problem say
        // that there is a duplicate
        return -1;
    }

    /**
     * Using cycle sort
     * Theta(n) time and Theta(1) space
     * modifies the input array
     *
     * Put the number at nums[0] in index 'nums[0]'. At some point because there
     * is a duplicate, we will find the same number again at nums[0].
     *
     * Visualize as removing the next node after head in the linked list cycle.
     * Initially we will put the start of the cycle in its index and when we traverse
     * the whole cycle again and come back to the start of the cycle, we find the
     * duplicate as the start of the cycle is already in its index.
     */
    static int solution3(std::vector<int> &nums)
    {
        while (nums[0] != nums[nums[0]])
            std::swap(nums[0], nums[nums[0]]);
        return nums[0];
    }

    /**
     * Brute force solution
     * Theta(n^2) time and Theta(1) space
     */
    static int solution4(const std::vector<int> &nums)
    {
        int n{static_cast<int>(nums.size())};
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (nums[i] == nums[j])
                    return nums[j];

        // We would never reach here as there is a duplicate that exists
        return -1;
    }

public:
    int findDuplicate(std::vector<int> &nums) { return solution3(nums); }
};