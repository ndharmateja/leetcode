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

    static void swap(std::vector<int> &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    /**
     * Using cycle sort
     * Theta(n) time and Theta(1) space
     * modifies the input array
     */
    static int solution3(std::vector<int> &nums)
    {
        while (nums[0] != nums[nums[0]])
            swap(nums, 0, nums[0]);
        return nums[0];
    }

public:
    int findDuplicate(std::vector<int> &nums) { return solution3(nums); }
};