#include <string>
#include <bitset>

class Solution
{
private:
    /**
     * Theta(n) time and Theta(1) space
     * end goes from 1 to n-1 and start goes from 0 to atmost n-1
     */
    static int sol1(const std::string &s)
    {
        /**
         * Invariant:
         * The sliding window at any point only contains unique characters
         */
        int n{static_cast<int>(s.size())};
        if (n == 0 || n == 1)
            return n;

        // ! start is inclusive but end is exclusive (like python string slicing)
        // Sliding window starts with just the first character in it (invariant maintained)
        int start{0}, end{1};
        int max_window_len{1}, curr_window_len{1};

        std::bitset<128> sliding_window_contains;
        sliding_window_contains[s[0]] = true;

        unsigned char curr_char;
        while (end < n)
        {
            // Get the current character and increment the end (to advance the
            // end of the sliding window)
            curr_char = s[end++];

            // If the curr_char is not in the current sliding window
            // we can add this character to increment the length of the
            // sliding window
            // ! We only need to check against the max length in the case that
            // ! curr_char isn't present in the sliding window as if it is already present
            // ! then the new sliding window's (after removing the earlier curr_char) length
            // ! cannot be greater than the current window's length
            if (!sliding_window_contains[curr_char])
            {
                sliding_window_contains[curr_char] = true;
                curr_window_len++;
                max_window_len = curr_window_len > max_window_len
                                     ? curr_window_len
                                     : max_window_len;
                continue;
            }

            // If the curr_char is already present, we keep removing chars
            // from the start of the sliding window until we remove the curr_char
            while (s[start] != curr_char)
                // Remove the start character from the bitset and increment start
                sliding_window_contains[s[start++]] = false;

            // At this point, start char is same as the curr_char
            // so we need to remove it from the bitset
            // ! Optimization: Since we are anyway going to add the same char (curr_char)
            // ! back to the bitset, we don't have to explicitly remove and add
            start++;

            // ! Optimization: Instead of decrementing curr_window_len throughout the while loop
            // ! we can update it at the end of the loop
            curr_window_len = end - start;
        }

        // Return the max value
        return max_window_len;
    }

public:
    int lengthOfLongestSubstring(const std::string &s) { return sol1(s); }
};