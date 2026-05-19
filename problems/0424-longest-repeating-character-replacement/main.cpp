#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

class Solution
{
private:
    static int find_longest_repeating_string_len(const std::string &s)
    {
        int n{static_cast<int>(s.size())};
        if (n == 1)
            return n;

        unsigned char curr_char = s[0];
        int curr_char_count{1}, max_count{1};
        for (int i = 1; i < n; i++)
        {
            if (s[i] == curr_char)
            {
                curr_char_count++;
                continue;
            }

            // New char then we can update the max
            max_count = std::max(max_count, curr_char_count);
            curr_char = s[i];
            curr_char_count = 1;
        }

        max_count = std::max(max_count, curr_char_count);
        return max_count;
    }

    /**
     * Invariant:
     * At any point there are exactly two characters in the sliding window
     * The sliding window is represented using indices start and end (end is exclusive like Python)
     * first_char represents the first character of the sliding window (as a number 'A' is 0 etc)
     * second_char represents the other char in the sliding window
     * and char_counts having the counts of two chars
     */
    static int sol1(const std::string &s, int k)
    {
        if (!k)
            return find_longest_repeating_string_len(s);

        // Init n and the char counts vector
        int n{static_cast<int>(s.size())};
        std::vector<int> char_counts(26);

        // Init the sliding window to maintain the invariant
        int start{0}, end{1};
        int first_char{s[0] - 'A'}, second_char;
        while (end < n && (s[end] - 'A') == first_char)
            end++;

        // At this point if end == n, it means we have reached the end
        // before finding a different character than the first char which means that all chars
        // are the same in the string
        if (end == n)
            return n;

        // Otherwise end will point to the first character that is different
        second_char = s[end] - 'A';
        end++;

        // At this point the sliding window has exactly two characters
        // and the first_char represents the first character of the sliding window
        // and the second_char represents the other char
        // s[:end] is the sliding window with s[end-1] being the second_char with only one occurrence
        // and all indices from [0, end-2] will have first_char
        // So we can update the char_counts
        char_counts[second_char] = 1;
        char_counts[first_char] = (end - 2) + 1;

        // At this point the invariant is established
        // We can make this window completely the same character with character replacement
        // as k >= 1
        int max_length{end - start};

        int curr_char;
        while (end < n)
        {
            curr_char = s[end++] - 'A';

            // If this character is the same as the first character or the second character
            // then we can extend the sliding window to maintain the invariant
            if (curr_char == first_char || curr_char == second_char)
            {
                // Increment the count of the curr char
                char_counts[curr_char]++;

                // At this point the invariant is established

                // See if we can form a string with same characters using character replacement
                // We can only do that if the smaller of the counts of first_char and second_char
                // is <= k
                if (std::min(char_counts[first_char], char_counts[second_char]) <= k)
                    max_length = std::max(max_length, end - start);

                // We can go to the next char of the string
                continue;
            }

            // At this point we have a new char, that is different from the first_char
            // and the second_char
            // Since the first_char is the first character of the string
            // we move the start of the sliding window until all occurrences of the first character are gone
            while (char_counts[first_char] && char_counts[second_char])
            {
                if (s[start] - 'A' == first_char)
                    char_counts[first_char]--;
                else
                    char_counts[second_char]--;
                start++;
            }

            // At this point the sliding window only contains the second_char
            // which we have to make it the first_char to maintain the invariant
            first_char = s[start] - 'A';

            // The second_char will be the new char and its count will be 1
            second_char = curr_char;
            char_counts[curr_char] = 1;

            // At this point the invariant is maintained again
            // We can form a string with same characters using character replacement
            // as k >= 1 and the new character only occurs once
            max_length = std::max(max_length, end - start);
        }

        return max_length;
    }

    /**
     * Function to print char counts
     */
    static void print_char_counts(const std::vector<int> &char_counts)
    {
        for (int i = 0; i < 26; i++)
            if (char_counts[i])
                std::cout << static_cast<char>(i + 'A') << " : " << char_counts[i] << " ";
        std::cout << std::endl;
    }

public:
    int characterReplacement(const std::string &s, int k) { return sol1(s, k); }
};

int main()
{
    std::cout << Solution().characterReplacement("AAAA", 0) << std::endl
              << std::endl;
    std::cout << Solution().characterReplacement("AABABBA", 1) << std::endl
              << std::endl;
    std::cout << Solution().characterReplacement("ABAB", 2) << std::endl
              << std::endl;
    std::cout << Solution().characterReplacement("AABABBA", 1) << std::endl
              << std::endl;
    return 0;
}