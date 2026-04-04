#include <vector>
#include <unordered_set>

class Solution
{
private:
    /**
     * Theta(n) time and Theta(n) space in the worst case
     */
    static int solution1(std::vector<int> &nums)
    {
        // Create an unordered set from the vector of ints
        std::unordered_set<int> set(nums.begin(), nums.end());
        int max_seq_length = 0;

        // For each value in the set, see if the number is start of the sequence
        // (by checking if number-1 is not part of the set) and if it is the start
        // of a sequence, we can count the length of the sequence by checking
        // number+1, number+2, ..
        // If the number is not the start of a sequence, we can skip it
        for (int num : set)
        {
            // If not the start of a sequence
            if (set.count(num - 1))
                continue;

            // If the start of a sequence count the length of the sequence
            int seq_length = 1;
            while (set.count(++num))
                seq_length++;

            // If this sequence's length is greater than max, update
            max_seq_length = std::max(max_seq_length, seq_length);
        }

        // Return the max sequence length
        return max_seq_length;
    }

public:
    int longestConsecutive(std::vector<int> &nums) { return solution1(nums); }
};