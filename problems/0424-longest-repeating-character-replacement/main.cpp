#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>

class Solution
{
    static int sol1(const std::string &s, int k)
    {
        std::array<int, 26> char_counts{};
        int start{0}, end{0}, n{static_cast<int>(s.size())};
        int global_max{0}, max_char_count;
        char c;
        while (end < n)
        {
            // Add char at end to the window
            c = s[end++];
            char_counts[c - 'A']++;

            // If the invariant still holds we can record this window length and move to the next one
            max_char_count = *std::max_element(char_counts.begin(), char_counts.end());
            if (max_char_count >= (end - start) - k)
            {
                global_max = std::max(global_max, end - start);
                continue;
            }

            // If the invariant is broken, remove characters from front until the invariant is satisfied
            while (true)
            {
                c = s[start++];
                char_counts[c - 'A']--;

                max_char_count = *std::max_element(char_counts.begin(), char_counts.end());
                if (max_char_count >= (end - start) - k)
                    break;
            }
            global_max = std::max(global_max, end - start);
        }

        return global_max;
    }

    /**
     * Same as solution 1, except we maintain the max count as we go through
     * different windows instead of spending Theta(26) time to find it for each
     * sliding window
     */
    static int sol2(const std::string &s, int k)
    {
        int start{0}, end{0}, n{static_cast<int>(s.size())};
        int global_max{0}, max_char_count{0};
        int new_count;
        int c;

        std::array<int, 26> char_counts{};
        std::unordered_map<int, std::bitset<26>> count_to_char_map;
        count_to_char_map.reserve(n);
        count_to_char_map[0].set();

        // Invariant : At any point, the window has the property that we could form the
        // result with the window length by replacing <= k chars

        while (end < n)
        {
            // Add char at end to the window
            c = s[end++] - 'A';
            new_count = ++char_counts[c];
            count_to_char_map[new_count - 1].reset(c);
            count_to_char_map[new_count].set(c);
            max_char_count = std::max(max_char_count, new_count);

            // If the invariant still holds we can record this window length and move to the next one
            if (max_char_count >= (end - start) - k)
            {
                global_max = std::max(global_max, end - start);
                continue;
            }

            // If the invariant is broken, remove characters from front until the invariant is satisfied
            while (true)
            {
                c = s[start++] - 'A';
                new_count = --char_counts[c];
                count_to_char_map[new_count + 1].reset(c);
                count_to_char_map[new_count].set(c);

                if (count_to_char_map[max_char_count].none())
                    max_char_count = new_count;

                if (max_char_count >= (end - start) - k)
                    break;
            }
            global_max = std::max(global_max, end - start);
        }

        return global_max;
    }

    /**
     * Same as solution 2, except we use a vector instead of an unordered_map
     * and also only track number of characters that occur at each count
     * instead of tracking all the characters that occur at each count
     */
    static int sol3(const std::string &s, int k)
    {
        int start{0}, end{0}, n{static_cast<int>(s.size())};
        int global_max{0}, max_char_count{0};
        int new_count;
        int c;

        std::array<int, 26> char_counts{};
        std::vector<char> freq_of_freq(n + 1);
        freq_of_freq[0] = 26;

        // Invariant : At any point, the window has the property that we could form the
        // result with the window length by replacing <= k chars

        while (end < n)
        {
            // Add char at end to the window
            c = s[end++] - 'A';
            new_count = ++char_counts[c];
            freq_of_freq[new_count - 1]--;
            freq_of_freq[new_count]++;
            max_char_count = std::max(max_char_count, new_count);

            // If the invariant still holds we can record this window length and move to the next one
            if (max_char_count >= (end - start) - k)
            {
                global_max = std::max(global_max, end - start);
                continue;
            }

            // If the invariant is broken, remove characters from front until the invariant is satisfied
            while (true)
            {
                c = s[start++] - 'A';
                new_count = --char_counts[c];
                freq_of_freq[new_count + 1]--;
                freq_of_freq[new_count]++;

                if (!freq_of_freq[max_char_count])
                    max_char_count = new_count;

                if (max_char_count >= (end - start) - k)
                    break;
            }
            global_max = std::max(global_max, end - start);
        }

        return global_max;
    }

    /**
     * Same as solution 3, except we don't shrink the sliding window
     * as we already recorded that size, we don't have to shrink.
     * So if invariant is broken we can just slide it until we find a better size
     */
    static int sol4(const std::string &s, int k)
    {
        int start{0}, end{0}, n{static_cast<int>(s.size())};
        int global_max{0}, max_char_count{0};
        int new_count;
        int start_c, end_c;

        std::array<int, 26> char_counts{};
        std::vector<char> freq_of_freq(n + 1);
        freq_of_freq[0] = 26;

        while (end < n)
        {
            // If the invariant does not hold true we can just slide the window
            // of the same length by one step to the right
            if (!(max_char_count >= (end - start) - k))
            {
                // If start character is same as the end character, then the counts won't change
                start_c = s[start++] - 'A';
                end_c = s[end++] - 'A';
                if (start_c == end_c)
                    continue;

                // Remove start char counts from the window
                new_count = --char_counts[start_c];
                freq_of_freq[new_count + 1]--;
                freq_of_freq[new_count]++;
                if (!freq_of_freq[max_char_count])
                    max_char_count = new_count;

                // Add end char counts to the window
                new_count = ++char_counts[end_c];
                freq_of_freq[new_count - 1]--;
                freq_of_freq[new_count]++;
                max_char_count = std::max(max_char_count, new_count);

                continue;
            }

            // At this point the invariant is satisfied, so we can record this length
            // and then increase the window size by 1
            global_max = std::max(global_max, end - start);

            // Add the end char to the sliding window
            end_c = s[end++] - 'A';
            new_count = ++char_counts[end_c];
            freq_of_freq[new_count - 1]--;
            freq_of_freq[new_count]++;
            max_char_count = std::max(max_char_count, new_count);
        }

        // We need to check and update global max at the end
        // This is for the case where adding the last character creates the biggest sliding window
        // but that is not recorded in the loop as we don't enter when end==n
        if (max_char_count >= (end - start) - k)
            global_max = std::max(global_max, end - start);
        return global_max;
    }

public:
    int characterReplacement(const std::string &s, int k) { return sol4(s, k); }
};