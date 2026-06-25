#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution
{
private:
    static void build_pattern_adj_list(const std::string &begin_word, const std::string &end_word, std::string &buffer,
                                       std::unordered_map<std::string, std::vector<int>> &pattern_adj_list,
                                       const std::vector<std::string> &word_list,
                                       int &begin_word_index, int &end_word_index, const int m, const int n)
    {
        for (int i = 0; i < n; i++)
        {
            // Check if end word and begin word occur in the word list
            buffer = word_list[i];
            if (buffer == end_word)
                end_word_index = i;
            if (buffer == begin_word)
                begin_word_index = i;

            // Use the buffer string as a buffer to create different patterns from the word
            // Eg: if word is "hot", then buffer takes the following values in each of the iterations
            // ["*ot", "h*t", "ho*"]
            for (int j = 0; j < m; j++)
            {
                // Create the pattern with the ith char being '*'
                unsigned char c_j = buffer[j];
                buffer[j] = '*';

                // Add the word to the adj list
                pattern_adj_list[buffer].push_back(i);

                // Reset the word for the next iteration
                buffer[j] = c_j;
            }
        }
    }

    /**
     * Same as solution2 except we don't duplicate the strings in the word list
     * in the adj list, queue, visited etc
     * We use integer indices to track the words and use the strings in the word list
     * as the single source of truth
     */
    static int sol(const std::string &begin_word, const std::string &end_word,
                   const std::vector<std::string> &word_list)
    {
        /**
         * Create the adjacency list of patterns
         *                         0      1      2      3      4      5
         * Say the word list is ["hot", "dot", "dog", "lot", "log", "cog"]
         * Then the pattern adjacency list will be
         * {
         *    "*ot": [0, 1, 3],
         *    "h*t": [0],
         *    "ho*": [0],
         *    "d*t": [1],
         *    "do*": [1, 2],
         *    "*og": [2, 4, 5],
         *    "d*g": [2],
         *    "l*t": [3],
         *    "lo*": [3, 4],
         *    "l*g": [4],
         *    "c*g": [5],
         *    "co*": [5]
         * }
         */

        // m keeps track of the length of the word, n keeps track of #words in the word list
        // end_word_index and begin_word_index keep track of the indices of end_word and begin_word
        // We are using a default value of 'n' for the begin_word as it need not occur in the word list
        // and we still need to make it work for the visited boolean vector
        // So if the begin word doesn't occur in the word list, we use an index of n for it
        int m{static_cast<int>(begin_word.size())}, n{static_cast<int>(word_list.size())};
        int end_word_index{-1}, begin_word_index{n};

        // The buffer string is used to create different patterns from the word
        // for the adjacency list and also for the neighbours in the BFS main loop
        std::string buffer(m, '\0');

        // Create the pattern adjacency list
        // For each word, we create all patterns and add the word index to all the pattern keys
        std::unordered_map<std::string, std::vector<int>> pattern_adj_list;
        build_pattern_adj_list(begin_word, end_word, buffer, pattern_adj_list, word_list,
                               begin_word_index, end_word_index, m, n);

        // Edge case, if endword is not in the wordlist, we can return 0
        if (end_word_index == -1)
            return 0;

        // Create the queue and visited for BFS
        // The visited vector need not be of size n+1 even though the begin word if
        // not present in the word list has an index of n+1 as, if the begin word is not
        // in the word list, it would not appear in any of the adjacency list keys
        // So we need not keep track of the begin word in the visited vector
        // If the begin word occurred in the word list, then it will be kept track of
        // by its index
        std::vector<bool> visited(n + 1, false);
        std::queue<int> queue;
        queue.push(begin_word_index);
        visited[begin_word_index] = true;

        // BFS main loop
        // layer by layer to keep track of distance
        int distance{1};
        while (!queue.empty())
        {
            int num_elements_layer{static_cast<int>(queue.size())};
            for (int i = 0; i < num_elements_layer; i++)
            {
                // Pop the next element and if it matches
                int curr_index = queue.front();
                queue.pop();

                // Add all the unvisited neighbours of the word to the queue
                buffer = curr_index == n ? begin_word : word_list[curr_index];
                for (int j = 0; j < m; j++)
                {
                    // Create the pattern with the jth char being '*'
                    // Say the word is "hot" and j is 1, then pattern is "h*t"
                    // c_j = 'o' to reset the jth char for the next iteration
                    unsigned char c_j = buffer[j];
                    buffer[j] = '*';

                    // Get all the neighbours with the matching pattern except for curr itself
                    // only if the pattern exists in the adjacency list
                    auto it = pattern_adj_list.find(buffer);
                    if (it != pattern_adj_list.end())
                        for (int neighbour_index : it->second)
                        {
                            // If the neighbour is the curr word itself (it is possible that they are
                            // the same as we are finding the neighbours based on the pattern)
                            // Eg: if curr is "hot" and pattern is "*ot", then "hot" also will be part of the
                            // "*ot" pattern in the adjacency list
                            if (neighbour_index == curr_index)
                                continue;

                            // If this is the answer we can return
                            if (neighbour_index == end_word_index)
                                return distance + 1;

                            // If the neighbour is already visited, we don't have to process it
                            if (visited[neighbour_index])
                                continue;

                            // !We mark the neighbour visited here to prevent duplicate insertions into the queue
                            // Mark the neighbour as visited and push it to the queue
                            visited[neighbour_index] = true;
                            queue.push(neighbour_index);
                        }

                    // Reset the word for the next iteration
                    buffer[j] = c_j;
                }
            }

            // As one layer is completed, we increment the distance for the next layer
            distance++;
        }

        // If we reach here, it means that there wasn't a path from the begin word to the end word
        return 0;
    }

public:
    int ladderLength(const std::string &begin_word, const std::string &end_word,
                     const std::vector<std::string> &word_list) { return sol(begin_word, end_word, word_list); }
};