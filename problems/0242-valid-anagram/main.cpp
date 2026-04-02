#include <string>
#include <algorithm>
#include <array>
#include <unordered_map>

class Solution
{
private:
    /**
     * Sorted strings should be the same if they are anagrams
     * Theta(n lgn + m lgm) solution
     * where n, m are the lengths of the strings
     */
    static bool solution1(std::string &s, std::string &t)
    {
        if (s.size() != t.size())
            return false;
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        return s == t;
    }

    /**
     * Two strings are anagrams if their char counts are same
     * Uses a fixed 26 length array to track the counts
     * Only works for lowercase english alphabets
     * Theta(n + m) time and Theta(26)=Theta(1) space
     */
    static bool solution2(const std::string &s, std::string &t)
    {
        if (s.size() != t.size())
            return false;

        // All elements in counts are init to 0
        // short is enough as the total number chars in each string <= 50000
        std::array<short, 26> s_counts{};
        std::array<short, 26> t_counts{};

        // Compute counts
        size_t n{s.size()};
        for (size_t i = 0; i < n; i++)
        {
            s_counts[static_cast<unsigned char>(s[i]) - 'a']++;
            t_counts[static_cast<unsigned char>(t[i]) - 'a']++;
        }

        // If the char counts for each string are same, it means that they are anagrams
        return s_counts == t_counts;
    }

    /**
     * Two strings are anagrams if their char counts are same
     * Uses an unordered map to track the counts of chars
     * Since it uses a map, it works for all kinds of chars
     * Theta(n + m) time and Theta(charset length)=Theta(1) space
     */
    static bool solution3(const std::string &s, std::string &t)
    {
        if (s.size() != t.size())
            return false;

        // All elements in counts are init to 0
        // short is enough as the total number chars in each string <= 50000
        std::unordered_map<char, int> s_counts{};
        std::unordered_map<char, int> t_counts{};

        // Compute counts
        size_t n{s.size()};
        for (size_t i = 0; i < n; i++)
        {
            s_counts[s[i]]++;
            t_counts[t[i]]++;
        }

        // If the char counts for each string are same, it means that they are anagrams
        return s_counts == t_counts;
    }

public:
    bool isAnagram(std::string &s, std::string &t) { return solution1(s, t); }
};