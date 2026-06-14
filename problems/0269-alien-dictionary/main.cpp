#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bitset>

class Solution
{
private:
    /**
     * Recursively builds the adj list of letter orderings and also builds
     * the in degreees for each of the vertices
     * Edge x -> y in the graph means that x comes before y in the alien
     * lexicographical ordering
     *
     * Invariants:
     * 1. The range of words in the subarray words[start:end] will all have
     *   the same prefix of length letter_index (note that end is exclusive).
     * 2. There are atleast two words in the words[start:end] range (otherwise)
     *   there is no information we can get about the letter ordering given
     *   just one word.
     */
    static bool build_adj_matrix(const std::vector<std::string> &words,
                                 int start, int end, unsigned letter_index,
                                 std::bitset<676> &adj_matrix,
                                 std::array<int, 26> &in_degrees)
    {
        while (start < end && words[start].size() <= letter_index)
            start++;
        if (end - start <= 1)
            return true;

        int range_char = words[start][letter_index] - 'a';
        int range_start = start, curr_range_index;
        for (curr_range_index = start + 1; curr_range_index < end; curr_range_index++)
        {
            if (words[curr_range_index].size() <= letter_index)
                return false;
            int curr_char = words[curr_range_index][letter_index] - 'a';
            if (curr_char == range_char)
                continue;

            // We are for the first time coming to a character that is different
            // from the character we are tracking for the range
            // So we can add an edge from the range_char to the curr_char
            // ! If adj_matrix is std::vector<std::vector<bool>>
            // ! When we do `auto has_edge = adj_matrix[r][c]`
            // ! then the type of has_edge is std::vector<bool>::reference
            // ! so we can directly change the underlying bit using has_edge = true
            // ! It is a special case for bool vectors as bool occupies only 1 bit
            // ! we can't have a direct reference to a bit (references are to bytes)

            // ! If adj_matrix is std::bitset<676>
            // ! When we do `auto has_edge = adj_matrix[index]`
            // ! then the type of has_edge is std::bitset::reference
            // ! so we can directly change the underlying bit using has_edge = true

            // If there already wasn't an edge, we create an edge in the adj matrix
            // and increment the indegree accordingly (we do this with an if condition
            // as we don't want multi edges for indegree in the graph)
            int row_major_index = range_char * 26 + curr_char;
            auto has_edge = adj_matrix[row_major_index];
            if (!has_edge)
            {
                has_edge = true;

                // ! We can do this as we are prescanning and making all valid chars'
                // ! indegrees to 0, so this won't be -1 at this point
                ++in_degrees[curr_char];
            }

            // The char at letter_index is same for all words in the words[range_start:curr_range_index] range,
            // so the prefix of length "letter_index + 1" will be the same for all the words
            // in the range words[range_start:curr_range_index]
            // so now we can recursively call the function starting at letter_index + 1
            // if there are atleast 2 words in the range
            if (curr_range_index - range_start >= 2)
                if (!build_adj_matrix(words, range_start, curr_range_index, letter_index + 1, adj_matrix, in_degrees))
                    return false;

            // Update the range_char and range_start values with the new char
            range_char = curr_char;
            range_start = curr_range_index;
        }

        // The last range (if exists) wouldn't be processed in the for loop
        if (curr_range_index - range_start >= 2)
            if (!build_adj_matrix(words, range_start, curr_range_index, letter_index + 1, adj_matrix, in_degrees))
                return false;
        return true;
    }

    static std::string sol1(const std::vector<std::string> &words)
    {
        // Ideas:
        // 1. indegrees computation during vs after building adj matrix
        // 2. int8_t and uint8_t instead of ints at appropriate places (be careful of ops)
        // 3. Eliminate queue and use the result string as the queue itself (as elements are
        //   never removed from the final string/array)
        // 4. Explicit zeroing of the indegrees by going through all the chars of the words
        //   vs adding an if condition to check if it is -1 before incrementing (num_chars also
        //   has to be taken care of)
        //
        // Improvements:
        // 1. std::bitset<676> instead of std::vector<std::vector<bool>> for adj matrix
        // 2. return true/false from the build_adj_matrix method instead of throwing an exception
        //   when there is an invalid order

        // Edge case
        // If there is only one word, we don't have any information about the ordering
        int num_words{static_cast<int>(words.size())};
        if (num_words == 1)
            return words.front();

        // After this step, the indegrees for all the characters that are present will be 0
        // and the indegrees for all the characters that are not present will be -1
        int num_chars{0};
        std::array<int, 26> in_degrees;
        in_degrees.fill(-1);
        for (int i = 0; i < num_words && num_chars != 26; i++)
        {
            const auto &word = words[i];
            for (unsigned char c : word)
            {
                int &c_in_degree = in_degrees[c - 'a'];
                if (c_in_degree == -1)
                {
                    num_chars++;
                    c_in_degree = 0;
                }
            }
        }

        // Build the adjacency matrix and the indegrees for the graph
        std::string result;
        std::bitset<676> adj_matrix;
        bool is_valid = build_adj_matrix(words, 0, num_words, 0, adj_matrix, in_degrees);
        if (!is_valid)
            return "";

        // See solution 2 of problem 210 for more details
        std::queue<int> queue;
        for (int i = 0; i < 26; i++)
            if (!in_degrees[i])
                queue.push(i);

        while (!queue.empty())
        {
            // Pop the next char in the queue
            int u = queue.front();
            queue.pop();

            // Add the char to the result string
            result.push_back(u + 'a');

            // Decrement the indegrees of all the edges from curr_char
            // and if they become 0 we can add them to the queue
            for (int v = 0; v < 26; v++)
            {
                // If there is an edge from u->v
                int row_major_index = u * 26 + v;
                if (adj_matrix[row_major_index])
                {
                    int &v_in_degree = in_degrees[v];
                    v_in_degree--;
                    if (!v_in_degree)
                        queue.push(v);
                }
            }
        }

        return (static_cast<int>(result.size()) == num_chars)
                   ? result
                   : "";
    }

public:
    std::string foreignDictionary(const std::vector<std::string> &words) { return sol1(words); }
};