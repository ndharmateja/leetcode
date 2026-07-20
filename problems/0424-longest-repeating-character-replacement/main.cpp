#include <vector>
#include <array>
#include <string>
#include <algorithm>

#include <iostream>

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

public:
    int characterReplacement(const std::string &s, int k) { return sol1(s, k); }
};