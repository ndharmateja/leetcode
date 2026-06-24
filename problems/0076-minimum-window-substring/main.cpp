#include <string>
#include <array>

class Solution
{
private:
    static inline const int ALPHABET_SIZE{52};

    static inline int get_index(unsigned char c)
    {
        if ('a' <= c && c <= 'z')
            return c - 'a';
        return 26 + (c - 'A');
    }

    static std::string sol1(const std::string &text, const std::string &pattern)
    {
        // Edge cases
        int m{static_cast<int>(text.size())}, n{static_cast<int>(pattern.size())};
        if (m < n)
            return "";

        // Compute the char counts and num unique characters in the pattern
        std::array<int, ALPHABET_SIZE> pattern_counts{0};
        int num_unique_chars{0};
        for (int i = 0; i < n; i++)
        {
            unsigned char c = pattern[i];
            int &count = pattern_counts[get_index(c)];
            if (!count)
                num_unique_chars++;
            count++;
        }

        // [start, end) keeps track of the sliding window
        // Invariant is that the sliding window contains each character atleast its count
        // number of times
        // Initially the sliding window is empty, so we increment end until it contains
        // all the characters of the pattern
        // We keep track of the variable num_chars_present which indicates the number of chars
        // in the pattern which appear atleast its count number of times in the window
        // If num_chars_present equals num_unique_chars, it means that the invariant is satisfied
        int start{0}, end{0}, num_chars_present{0};
        std::array<int, ALPHABET_SIZE> window_counts{0};
        while (end < m && num_chars_present < num_unique_chars)
        {
            // If this character doesn't appear in the pattern, we can skip it
            unsigned char c = text[end++];
            int c_index = get_index(c);
            int &pattern_count = pattern_counts[c_index];
            if (!pattern_count)
                continue;

            // Increment the character's count
            int &window_count = window_counts[c_index];
            window_count++;

            // If at this point for the current char, the count equals that of the window
            // this character appears enough times in the window at this point for the
            // first time, so we can increment num_chars_present
            if (window_count == pattern_count)
                num_chars_present++;
        }

        // At this point if num_chars_present < num_unique_chars it means that we don't have
        // a solution
        if (num_chars_present < num_unique_chars)
            return "";

        // At this point the window contains all the characters from the pattern
        // Initialize the optimal window
        int opt_start{start}, opt_end{end};

        // The invariant for the window is maintained at the start of each loop
        while (end <= m)
        {
            // ! Note: We don't have to explicity decrement and increment num_chars_present
            // ! when we break and fix it as we are going to fix the invariant once we
            // ! break it
            // Keep removing characters from the start of the window until a character present
            // in the pattern is dropped, which breaks the invariant for the first time
            // Eg: if window is ADKHSITHSABDC and the pattern is ABC
            //    we keep removing characters until the window becomes BDC
            unsigned char c;
            while (true)
            {
                // If this character is present in the pattern and its count in both
                // the pattern and the window are same, then removing this character
                // would disturb the invariant (for the first time)
                c = text[start++];
                int c_index = get_index(c);

                int pattern_count = pattern_counts[c_index];
                if (!pattern_count)
                    continue;

                int &window_count = window_counts[c_index];
                window_count--;
                if (window_count < pattern_count)
                    break;
            }

            // At this point character at start-1 was the first character that disturbed the
            // invariant => [start-1, end) is a window that satisfies the invariant
            // If that window has a smaller length than the current optimum, we record it
            if (end - (start - 1) < opt_end - opt_start)
            {
                opt_start = start - 1;
                opt_end = end;
            }

            // TODO: add explanation why we need this check here
            if (end == m)
                break;

            // c is the character that broke the invariant
            // So we keep incrementing the window until we add the char c to the window
            // We also need to increase the counts of the chars that are present in the
            // pattern along the way
            // The loop breaks when end-1 is matching c (as we are also incrementing end)
            while (end < m)
            {
                unsigned char end_c = text[end++];
                int end_c_index = get_index(end_c);
                if (!pattern_counts[end_c_index])
                    continue;

                window_counts[end_c_index]++;
                if (end_c == c)
                    break;
            }

            // At this point if we have reached the end without finding the char c
            // then we can exit the loop
            // If the char at end-1 is not c, it means we have reached the end
            // without finding it
            if (text[end - 1] != c)
                break;
        }

        // Return the result
        // which is the substring in [opt_start, opt_end)
        return text.substr(opt_start, opt_end - opt_start);
    }

public:
    std::string minWindow(const std::string &text, const std::string &pattern) { return sol1(text, pattern); }
};