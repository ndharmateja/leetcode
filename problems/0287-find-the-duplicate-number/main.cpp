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
     * Using a hashset
     * Theta(N) time and Theta(N) space solution
     */
    static int solution2(const std::vector<int> &nums)
    {
        std::unordered_set<int> set(nums.size());
        for (const int &num : nums)
        {
            if (set.count(num))
                return num;
            set.emplace(num);
        }

        // We would never reach here as the constraints of the problem say
        // that there is a duplicate
        return -1;
    }

public:
    int findDuplicate(std::vector<int> &nums) { return solution2(nums); }
};