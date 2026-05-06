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

        return 0;
    }

    /**
     * Same as solution2 except we don't duplicate the strings in the word list
     * in the adj list, queue, visited etc
     * We use integer indices to track the words and use the strings in the word list
     * as the single source of truth
     */
    static int solution3(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list)
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
        std::vector<bool> visited(n, false);
        std::queue<int> queue;
        queue.push(begin_word_index);

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

        // We won't reach here as the end word is guaranteed to be in the word list
        return 0;
    }

    /**
     * Bidirectional BFS
     * TODO: modularity, add running time and space, add detailed explanation and argument for correctness
     */
    static int solution4(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list)
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

        // Edge case, if endword is not in the wordlist, we can return 0
        if (end_word_index == -1)
            return 0;

        // Start BFS from both the begin word and the end word
        // Create the queue and visited for BFS
        // The visited vector need not be of size n+1 even though the begin word if
        // not present in the word list has an index of n+1 as, if the begin word is not
        // in the word list, it would not appear in any of the adjacency list keys
        // So we need not keep track of the begin word in the visited vector
        // If the begin word occurred in the word list, then it will be kept track of
        // by its index

        // Data structures for BFS from the begin word
        std::vector<bool> visited_front(n, false);
        std::queue<int> queue_front;
        queue_front.push(begin_word_index);
        int distance_from_front{1};

        // Data structures for BFS from the end word
        std::vector<bool> visited_back(n, false);
        std::queue<int> queue_back;
        queue_back.push(end_word_index);
        int distance_from_back{1};

        while (!queue_front.empty() && !queue_back.empty())
        {
            // Run a layer of BFS from the front side
            int num_elements_layer{static_cast<int>(queue_front.size())};
            for (int i = 0; i < num_elements_layer; i++)
            {
                // Pop the next element and if it matches
                int curr_index = queue_front.front();
                queue_front.pop();

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

                            // If we directly encounter the end word we can return
                            if (neighbour_index == end_word_index)
                                return distance_from_front + 1;

                            // If the neighbour is already visited, we don't have to process it
                            if (visited_front[neighbour_index])
                                continue;

                            // If this word was already visited by the BFS from the back
                            // We found the shortest path, length = (distance_from_front + 1) + (distance_from_back) - 1;
                            if (visited_back[neighbour_index])
                                return distance_from_front + distance_from_back;

                            // !We mark the neighbour visited here to prevent duplicate insertions into the queue
                            // Mark the neighbour as visited and push it to the queue
                            visited_front[neighbour_index] = true;
                            queue_front.push(neighbour_index);
                        }

                    // Reset the word for the next iteration
                    buffer[j] = c_j;
                }
            }

            // As one layer is completed, we increment the distance for the next layer
            distance_from_front++;

            // Run a layer of BFS from the back side
            num_elements_layer = static_cast<int>(queue_back.size());
            for (int i = 0; i < num_elements_layer; i++)
            {
                // Pop the next element and if it matches
                int curr_index = queue_back.front();
                queue_back.pop();

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

                            // If the neighbour is already visited, we don't have to process it
                            if (visited_back[neighbour_index])
                                continue;

                            // If this word was already visited by the BFS from the back
                            // We found the shortest path
                            if (visited_front[neighbour_index])
                                return distance_from_front + distance_from_back;

                            // !We mark the neighbour visited here to prevent duplicate insertions into the queue
                            // Mark the neighbour as visited and push it to the queue
                            visited_back[neighbour_index] = true;
                            queue_back.push(neighbour_index);
                        }

                    // Reset the word for the next iteration
                    buffer[j] = c_j;
                }
            }

            // As one layer is completed, we increment the distance for the next layer
            distance_from_back++;
        }

        // We would not reach here
        return 0;
    }

public:
    int ladderLength(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list) { return solution4(begin_word, end_word, word_list); }
};