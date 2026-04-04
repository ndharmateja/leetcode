#include <vector>
#include <string>

/**
 * Method:
 * 1. ["apple", "banana", "bubbleboyandmoops"]
 * 2. Say delimiter is '#', we encode the list to
 * "5#apple6#banana17#bubbleboyandmoops"
 * 3. We store the number of chars of word and a delimiter (delimiter is
 * needed because first char of word could be a digit)
 * 4. While decoding we can get num chars and get the numchars number of
 * characters to form a word (doesn't matter even if the words themselves
 * contain delimiters as we have the numChars in the word)
 */
class Solution
{
private:
    static const char delimiter = '#';

public:
    std::string encode(const std::vector<std::string> &strs)
    {
        // Precalculate the total length of the encoded string
        // so that we can avoid multiple reallocations
        int encoded_string_size = 0;
        for (const auto &str : strs)
            encoded_string_size += std::to_string(str.size()).size() + 1 + str.size();

        std::string encoded;
        encoded.reserve(encoded_string_size);
        for (const auto &str : strs)
        {
            encoded += std::to_string(str.size());
            encoded += delimiter;
            encoded += str;
        }
        return encoded;
    }

    std::vector<std::string> decode(const std::string &s)
    {
        // Init variables
        std::vector<std::string> result;
        int i{0}, n{static_cast<int>(s.size())};

        while (i < n)
        {
            // ax^3 + bx^2 + cx + d = ((ax + b)x + c)x + d
            int next_string_length = 0;
            unsigned char c;
            while ((c = s[i++]) != delimiter)
                next_string_length = (next_string_length * 10) + (c - '0');

            // At this point i was incremented to cross the delimiter too
            // i will point to the character after the delimiter
            // Extract the substring and add it to the result
            result.push_back(s.substr(i, next_string_length));

            // Increment i to point to the start of the length of the next string
            i += next_string_length;
        }
        return result;
    }
};
