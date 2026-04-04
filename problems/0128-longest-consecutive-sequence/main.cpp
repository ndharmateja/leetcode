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

    /**
     * Similar to solution2 except we don't make the numbers unique
     */
    static int solution3(std::vector<int> &nums)
    {
        // Take only the unique elements and sort it
        std::sort(nums.begin(), nums.end());

        // Return the max sequence length from a sorted vector of unique numbers
        return find_longest_consecutive_seq_len_in_sorted(nums);
    }

    /**
     * TODO: implement own version of radix sort
     *
     * Radix sort
     * Reference: Gemini
     *
     * LSD Radix Sort for 32-bit Signed Integers
     * Space: O(n) | Time: Theta(4 * (n + 256))
     * Optimization: Double Buffering to avoid O(n) vector copies.
     */
    static void radix_sort(std::vector<int> &nums)
    {
        int n = static_cast<int>(nums.size());
        if (n < 2)
            return;

        std::vector<int> buffer(n);
        std::vector<int> *src = &nums;
        std::vector<int> *dst = &buffer;

        // 4 passes, 8 bits (one byte) each
        for (int shift = 0; shift < 32; shift += 8)
        {
            int count[256] = {0};
            for (int x : *src)
                count[(x >> shift) & 0xFF]++;

            // Pass 4 (shift 24): Handle Two's Complement Signed Integers
            if (shift == 24)
            {
                int tmp = count[128];
                count[128] = 0;
                // Negative numbers (128-255) come first in signed order
                for (int i = 129; i < 256; ++i)
                {
                    int next = count[i];
                    count[i] = count[i - 1] + tmp;
                    tmp = next;
                }
                // Positive numbers (0-127) come after negatives
                int first_pos = tmp + count[255];
                tmp = count[0];
                count[0] = first_pos;
                for (int i = 1; i < 128; ++i)
                {
                    int next = count[i];
                    count[i] = count[i - 1] + tmp;
                    tmp = next;
                }
            }
            else
            {
                // Standard Counting Sort Prefix Sum
                int start = 0;
                for (int i = 0; i < 256; ++i)
                {
                    int tmp = count[i];
                    count[i] = start;
                    start += tmp;
                }
            }

            // Move data to destination buffer
            for (int x : *src)
                (*dst)[count[(x >> shift) & 0xFF]++] = x;

            // DOUBLE BUFFERING: Swap pointers instead of copying vector data
            std::swap(src, dst);
        }

        // After 4 swaps, src might point to the local 'buffer' vector.
        // If so, move the data back into the original 'nums'.
        if (src != &nums)
        {
            nums = std::move(buffer);
        }
    }

    /**
     * Exactly same as solution 2 except we use radix sort of the numbers
     * instead of using std::sort
     */
    static int solution4(std::vector<int> &nums)
    {
        // Take only the unique elements and sort it
        radix_sort(nums);

        // Return the max sequence length from a sorted vector of unique numbers
        return find_longest_consecutive_seq_len_in_sorted(nums);
    }

public:
    int longestConsecutive(std::vector<int> &nums) { return solution2(nums); }
};