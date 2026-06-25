#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

class Solution
{
private:
    /**
     * BFS based solution that finds the neighbours dynamically for each word
     * by mutating each character to a-z
     */
    static int solution1(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list)
    {
        // Create a unordered set of the word list
        std::unordered_set<std::string> words_set;
        words_set.reserve(word_list.size()); // Pre-allocate buckets to avoid rehashes
        for (const std::string &word : word_list)
            words_set.insert(word);

        // Base case
        if (!words_set.count(end_word))
            return 0;

        // Create the queue and visited for BFS
        std::queue<std::string> queue;
        std::unordered_set<std::string> visited;
        queue.push(begin_word);

        // BFS main loop
        // layer by layer to keep track of distance
        int distance{1};
        while (!queue.empty())
        {
            int num_elements_layer{static_cast<int>(queue.size())};
            for (int i = 0; i < num_elements_layer; i++)
            {
                // Pop the next element and if it matches
                std::string curr = queue.front();
                queue.pop();
                if (curr == end_word)
                    return distance;

                // Add all the unvisited neighbours of the word to the queue
                for (int i = 0; i < curr.size(); i++)
                {
                    std::string neighbour = curr;
                    for (char c2 = 'a'; c2 <= 'z'; c2++)
                    {
                        if (c2 == curr[i])
                            continue;
                        neighbour[i] = c2;

                        //
                        if (!visited.count(neighbour) && words_set.count(neighbour))
                        {
                            queue.push(neighbour);
                            visited.insert(neighbour);
                        }
                    }
                }
            }
            distance++;
        }

        // If we reach here, it means that there wasn't a path from the begin word to the end word
        return 0;
    }

    /**
     * BFS based solution that builds the adjacency list of patterns
     */
    static int solution2(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list)
    {
        /**
         * Create the adjacency list of patterns
         * Say the word list is ["hot", "dot", "dog", "lot", "log", "cog"]
         * Then the pattern adjacency list will be
         * {
         *    "*ot": ["hot", "dot", "lot"],
         *    "h*t": ["hot"],
         *    "ho*": ["hot"],
         *    "d*t": ["dot"],
         *    "do*": ["dot", "dog"],
         *    "*og": ["dog", "log", "cog"],
         *    "d*g": ["dog"],
         *    "l*t": ["lot"],
         *    "lo*": ["lot", "log"],
         *    "l*g": ["log"],
         *    "c*g": ["cog"],
         *    "co*": ["cog"]
         * }
         */
        int m{static_cast<int>(begin_word.size())};
        std::string buffer(m, '\0');
        std::unordered_map<std::string, std::vector<std::string>> pattern_adj_list;
        bool endword_exists{false};
        for (const std::string &word : word_list)
        {
            if (word == end_word)
                endword_exists = true;

            // Use the buffer string as a buffer to create different patterns from the word
            // Eg: if word is "hot", then buffer takes the following values in each of the iterations
            // ["*ot", "h*t", "ho*"]
            buffer = word;
            for (int i = 0; i < m; i++)
            {
                // Create the pattern with the ith char being '*'
                buffer[i] = '*';

                // Add the word to the adj list
                pattern_adj_list[buffer].push_back(word);

                // Reset the word for the next iteration
                buffer[i] = word[i];
            }
        }

        // Edge case, if endword is not in the wordlist, we can return 0
        if (!endword_exists)
            return 0;

        // Create the queue and visited for BFS
        std::queue<std::string> queue;
        std::unordered_set<std::string> visited;
        queue.push(begin_word);

        // BFS main loop
        // layer by layer to keep track of distance
        int distance{1};
        while (!queue.empty())
        {
            int num_elements_layer{static_cast<int>(queue.size())};
            for (int i = 0; i < num_elements_layer; i++)
            {
                // Pop the next element and if it matches
                std::string curr = queue.front();
                queue.pop();

                // Add all the unvisited neighbours of the word to the queue
                buffer = curr;
                for (int i = 0; i < m; i++)
                {
                    // Create the pattern with the ith char being '*'
                    buffer[i] = '*';

                    // Get all the neighbours with the matching pattern except for curr itself
                    for (const std::string &neighbour : pattern_adj_list[buffer])
                    {
                        if (neighbour == curr)
                            continue;
                        if (neighbour == end_word)
                            return distance + 1;
                        if (visited.count(neighbour))
                            continue;
                        queue.push(neighbour);
                        visited.insert(neighbour);
                    }

                    // Reset the word for the next iteration
                    buffer[i] = curr[i];
                }
            }
            distance++;
        }

        // If we reach here, it means that there wasn't a path from the begin word to the end word
        return 0;
    }

public:
    int ladderLength(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list) { return solution2(begin_word, end_word, word_list); }
};