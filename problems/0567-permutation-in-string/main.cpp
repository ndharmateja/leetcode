#include <string>
#include <array>
#include <cstdint>

class Solution
{
private:
    static inline const int ALPHABET_SIZE{26};

    /**
     * Computes char counts of s[:num_chars] and stores them in the counts array
     */
    static inline void compute_char_counts(std::array<uint16_t, ALPHABET_SIZE> &counts, const std::string &s, int num_chars)
    {
        for (int i = 0; i < num_chars; i++)
        {
            unsigned char c = s[i];
            counts[c - 'a']++;
        }
    }

    /**
     * Returns true if counts1 and counts are the same, false otherwise
     */
    static inline bool are_char_counts_same(std::array<uint16_t, ALPHABET_SIZE> &counts1, std::array<uint16_t, ALPHABET_SIZE> &counts2)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (counts1[i] != counts2[i])
                return false;
        return true;
    }

    /**
     * Sliding window solution with character counts
     *
     * O(ALPHABET_SIZE * n2) time and Theta(ALPHABET_SIZE) space
     * where n2 = #chars in s2
     */
    static bool sol1(const std::string &s1, const std::string &s2)
    {
        // If s2's length is less than s1's length
        // then s1 cannot exist as a permutation inside s2
        int n1{static_cast<int>(s1.size())}, n2{static_cast<int>(s2.size())};
        if (n2 < n1)
            return false;

        // We use a sliding window with same length as s1
        // Get the char counts of s1 and also the sliding window (which is the
        // first n1 chars of s2)
        // We can use uint16_t as the max count is 10000 according to leetcode constraints
        std::array<uint16_t, ALPHABET_SIZE> s1_char_counts{};
        std::array<uint16_t, ALPHABET_SIZE> window_char_counts{};
        compute_char_counts(s1_char_counts, s1, n1);
        compute_char_counts(window_char_counts, s2, n1);

        // If the sliding window and s1 are permutations of each other
        // then their char counts should be the same
        if (are_char_counts_same(s1_char_counts, window_char_counts))
            return true;

        // Keep moving the sliding window one step to the right each iteration
        // seeing if it is a permutation by comparing the char counts
        // Sliding window is the range [start, end)
        int start{0}, end{n1};
        while (end < n2)
        {
            // Remove the start from the sliding window and add end to it
            window_char_counts[s2[start++] - 'a']--;
            window_char_counts[s2[end++] - 'a']++;

            // If they are permutations of each other then we can return true
            if (are_char_counts_same(s1_char_counts, window_char_counts))
                return true;
        }

        // If we reached here it means that none of sliding windows were
        // a permutation of s1, so we can return false
        return false;
    }

public:
    bool checkInclusion(const std::string &s1, const std::string &s2) { return sol1(s1, s2); }
};