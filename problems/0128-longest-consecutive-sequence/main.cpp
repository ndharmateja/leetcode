#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution
{
private:
    /**
     * Theta(n) time and Theta(n) space in the worst case
     */
    static int solution1(const std::vector<int> &nums)
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

    /**
     * Gets the length of the longest consecutive sequence (of unique values) in a sorted array
     */
    static int find_longest_consecutive_seq_len_in_sorted(const std::vector<int> &nums)
    {
        // If array is empty return 0
        if (nums.empty())
            return 0;

        int n{static_cast<int>(nums.size())}, curr_len{1}, max_len{0};
        for (int i = 1; i < n; i++)
        {
            // If the curr value = prev value => part of the same sequence
            // but this value won't be part of the sequence length
            if (nums[i] == nums[i - 1])
                continue;

            // If the curr value = prev value + 1 => part of the same sequence
            if (nums[i] == nums[i - 1] + 1)
            {
                curr_len++;
                continue;
            }

            // Otherwise it is the start of a new sequence
            // Update the max sequence length and reset curr sequence length
            max_len = std::max(max_len, curr_len);
            curr_len = 1;
        }

        // Update the max sequence length once at the end for the last sequence
        max_len = std::max(max_len, curr_len);
        return max_len;
    }

    static int solution2(const std::vector<int> &nums)
    {
        // Take only the unique elements and sort it
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> unique_nums(set.begin(), set.end());
        std::sort(unique_nums.begin(), unique_nums.end());

        // Return the max sequence length from a sorted vector of unique numbers
        return find_longest_consecutive_seq_len_in_sorted(unique_nums);
    }
public:
    int longestConsecutive(std::vector<int> &nums) { return solution1(nums); }
};