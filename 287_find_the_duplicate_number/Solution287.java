class Solution {
    // O(n) time and O(1) space
    // Reference: https://youtu.be/wjYnzkAhcNk?t=375
    // Floyd's Algorithm
    // Method:
    // 1. Use fast and slow pointers to detect if cycle exists
    // 2. If fast reaches end, => no cycle
    // 3. fast and slow become equal at some node
    // 4. From that node, the start of cycle is at the same distance
    // from the head of the linked list
    // 5. So we can start another slow pointer at the head and move the slow2
    // pointer and the slow pointer (where fast and slow met) by one node
    // to eventually meet up at the start of the cycle
    //
    // To see how this problem is exactly same as the detection of
    // start of cycle in a linked list see method.jpeg
    public int findDuplicate(int[] nums) {
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast)
                break;
        }

        int slow2 = 0;
        while (slow != slow2) {
            slow = nums[slow];
            slow2 = nums[slow2];
        }

        return slow;
    }
}