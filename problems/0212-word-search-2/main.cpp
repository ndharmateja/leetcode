#include <vector>
#include <string>
#include <utility>
#include <array>

struct TrieNode
{
    bool is_word;
    int n;
    std::array<TrieNode *, 26> children;

    TrieNode() : is_word{false}, n{0}
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }

    ~TrieNode()
    {
        for (auto ptr : children)
            delete ptr;
    }
};

class Trie
{
private:
    TrieNode *root;

    /**
     * Recursively helper method to insert
     * Invariant is that node (if exists) would correspond to the word[:d] prefix
     * and if the node doesn't exist, it would be created.
     *
     * ! The given node need not be null unlike the invariants of the remove
     * ! collect_keys_that_match methods
     */
    TrieNode *insert(TrieNode *node, const std::string &word, int d)
    {
        // The invariant is that node (if exists) corresponds to the word[:d] prefix
        // of the word
        // If the node doesn't exist then we create it (with a count 0)
        if (!node)
            node = new TrieNode();

        // If d == word's length, it means that this is the node that corresponds to
        // word[:d] = word[:word_len] which is the full word
        // which means if this wasn't already a word, then we make it a word
        // and exit (after incrementing the count)
        if (d == static_cast<int>(word.size()))
        {
            // If it is already a word, then this word already exists
            // and we don't need to do anything at all
            if (node->is_word)
                return node;

            // At this point the node is not a valid word, so we make it a valid word
            // and increment its count and exit the function as there is nothing else to do
            node->is_word = true;
            node->n++;
            return node;
        }

        // If d < word's length, we need to continue the insertion
        int child_idx = word[d] - 'a';

        // ! Note that child_node is a reference to the element at the
        // ! child_idx in the children vector
        TrieNode *&child_node = node->children[child_idx];

        // We are storing the old count where we need to insert to figure out if we need to
        // increment the count of the current node
        int old_count = child_node ? child_node->n : 0;
        child_node = insert(child_node, word, d + 1);

        // If the child's count changed after the insertion, it means that a new key was
        // successfully added to the trie (as a descendant of the current node)
        // so we increment the count of the current node and return it
        if (child_node->n != old_count)
            node->n++;
        return node;
    }

    /**
     * Recursive helper method to remove
     * Invariant is that we assume that node is going to be not null
     * (to prevent an extra function call for the null check)
     * and word[:d] is the string corresponding to the given node
     *
     * ! We don't need the remove function to return the pointer of the
     * ! new root of the subtrie as we are not deleting nodes. We are only
     * ! decrementing the counts
     */
    void remove(TrieNode *node, const std::string &word, int d)
    {
        // If d equals to the word's length
        // then it means that word[:d] = word[:word_len] (according to the invariant)
        // is the word corresponding to the given node which is the full word
        // So if this node corresponds to a full word, we can mark it not a valid word
        // and decrement the count of this node
        if (d == static_cast<int>(word.size()) && node->is_word)
        {
            node->is_word = false;
            node->n--;
            return;
        }

        // If d < word's length, it means that we still haven't reached the end of the word
        // So we check if the appropriate child link is present and call delete on that
        // recursively
        else
        {
            // ! Note that child_node is a reference to the child_idx index in the
            // ! children vector so that we can avoid further lookups while accessing/updating
            int child_idx = word[d] - 'a';
            TrieNode *&child_node = node->children[child_idx];
            if (child_node)
            {
                // Store the old count to check if the current node's count
                // should be updated
                int old_child_n = child_node->n;
                remove(child_node, word, d + 1);

                // Get the new child's count and update curr node's count accordingly
                // There is a possibility that the child's count won't change
                // if nothing was deleted, in which case we don't have
                // There is also the possibility that the remove method returns nullptr
                // if the child node was removed from the trie
                // We update the count of the curr node
                // The only possibility of change is that the child's size decreases by 1
                // or if the child gets deleted
                // Either way we need to just decrement the curr node's size by 1

                // ! int new_child_n = child_node ? child_node->n : 0
                // ! if (new_child_n < old_child_n)
                // !    node->n--;
                // ! This should be the actual code but what it essentially boils down to
                // ! is that if the child node becomes null (it wasn't null earlier as we only
                // ! try to delete the child node if it is not null) or if the size of the child
                // ! node after delete is not the same as the old count, we can decrement
                // ! the curr node's count.
                if (child_node->n != old_child_n)
                    node->n--;
            }
        }
    }

public:
    Trie() : root{new TrieNode()} {}
    ~Trie() { delete root; }

    TrieNode *get_root() { return root; }

    /**
     * ! Root is never null. So we can directly return root's size.
     */
    int size() { return root->n; }
    bool empty() { return root->n == 0; }

    /**
     * Inserts the given word into the trie as a key
     */
    void insert(const std::string &word) { root = insert(root, word, 0); }

    /**
     * Removes the given word from the trie if it exists
     * and does nothing otherwise
     *
     * ! Root is never going to be null, so we wouldn't need to update it
     * ! So we don't have to do the regular pattern of
     * ! root = remove(root, word, 0)
     * ! We don't even have to make the helper remove method return a TrieNode *
     * ! as we aren't deleting node objects
     */
    void remove(const std::string &word) { remove(root, word, 0); }
};

class Solution
{
private:
    static constexpr int drs[] = {-1, 1, 0, 0};
    static constexpr int dcs[] = {0, 0, -1, 1};

    /**
     * Invariant is that curr_node is not null and has a non-zero count.
     * buffer is the string corresponding to curr_node in the trie.
     * And the last character of the buffer is board[r][c].
     */
    static void dfs(std::vector<std::vector<char>> &board, std::string &buffer,
                    int r, int c, int m, int n, Trie &trie,
                    TrieNode *curr_node, std::vector<std::string> &result)
    {
        // If this node is a full word, then we have found a word on the board
        // We can remove this word from the trie as we don't want to find
        // duplicates of the same word and removing found words prunes the search
        // space on the board
        if (curr_node->is_word)
        {
            result.push_back(buffer);
            trie.remove(buffer);

            // Pruning:
            // After removing the word, if the count of curr_node becomes 0
            // it means that there are no more explorations needed with this prefix
            // and we can exit the dfs on the prefix of buffer
            // This saves us a lot of time as we don't need to explore any other paths
            // with this prefix
            if (!curr_node->n)
                return;
        }

        // Mark this cell as visited so that we don't use this cell as part of further words
        // in the recursive dfs calls
        unsigned char char_rc = board[r][c];
        board[r][c] = '#';

        // Visit all the unvisited neighbours of the current cell that are part of the trie path
        for (int i = 0; i < 4; i++)
        {
            // Get the coordinates of the new cell
            int new_r = r + drs[i];
            int new_c = c + dcs[i];

            // If the new cell is out of bounds, we can skip it
            if (new_r < 0 || m <= new_r)
                continue;
            if (new_c < 0 || n <= new_c)
                continue;

            // If child character is already visited then we don't have to visit it
            unsigned char child_char = board[new_r][new_c];
            if (child_char == '#')
                continue;

            // ! We not only want the child node to be not null but we also need its count to be non-zero
            TrieNode *child_node = curr_node->children[child_char - 'a'];
            if (child_node && child_node->n)
            {
                buffer.push_back(child_char);
                dfs(board, buffer, new_r, new_c, m, n, trie, child_node, result);
                buffer.pop_back();
            }
        }

        // Unmark this cell as visited because we are backtracking and we are done with the dfs call
        // on the current cell
        board[r][c] = char_rc;
    }

    static std::vector<std::string> sol1(
        std::vector<std::vector<char>> &board,
        const std::vector<std::string> &words)
    {
        /**
         * Explanation:
         * 1. For the full implementation and explanation of the trie, see the following reference:
         * https://github.com/ndharmateja/data-structures-cpp/tree/master/data-structures/tries
         *
         * Improvements:
         * 1. Added the delete functionality (without deleting the actual nodes from memory
         *    as we need hold of the pointers in the parent calls of dfs but only by marking is_word false).
         *    Time limit exceeded to ~43% improvement on leetcode.
         * 2. Added the node counts to the nodes so that we don't traverse along the trie whose
         *    node counts are 0 (same as a null node but we need the node pointers). ~43% to ~93.5% improvement.
         * 3. Mutating the cells of the board itself to say '#' to indicate that they have been
         *    visited instead of a separate vector<vector<bool>>. ~93.5% to ~95% improvement.
         * 4. Change the following code
         *    From:
         *    static inline const std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
         *    To:
         *    static constexpr int drs[] = {-1, 1, 0, 0};
         *    static constexpr int dcs[] = {0, 0, -1, 1};
         *    Leetcode ~95% to ~96.2% improvement.
         */

        // Create a trie of words for easily checking validity of words
        // and also record the max word length to reserve the string length of the buffer
        Trie trie;
        int max_word_length{0}, word_length;
        for (const auto &word : words)
        {
            trie.insert(word);
            word_length = static_cast<int>(word.size());
            max_word_length = word_length > max_word_length
                                  ? word_length
                                  : max_word_length;
        }

        // From each cell on the board, do a dfs looking for words
        // with the first letter of the word as that cell
        int m{static_cast<int>(board.size())}, n{static_cast<int>(board[0].size())};

        // The buffer is the string that keeps track of the corresponding strings
        // along the path as we run the DFS
        // We know it can't be longer than the max word length that is in the trie
        // So we reserve it to prevent multiple resizes
        std::string buffer;
        buffer.reserve(max_word_length);

        // The result is the list of words found in the grid
        std::vector<std::string> result;

        // Run DFS starting from each of the cells to find the words using backtracking
        // We only need to keep traversing the cells as long as the trie has words in it
        // We are deleting the words in the trie as soon as we find them
        // So if we run out of words in the trie, then there is no point in continuing
        // the DFS from the remaning cells
        TrieNode *root = trie.get_root();
        for (int r = 0; r < m && !trie.empty(); r++)
            for (int c = 0; c < n && !trie.empty(); c++)
            {
                unsigned char ch = board[r][c];
                TrieNode *curr_node = root;
                curr_node = curr_node->children[ch - 'a'];

                // ! We not only want the curr_node to be not null but we also need its count to be non-zero
                if (curr_node && curr_node->n)
                {
                    buffer.push_back(ch);
                    dfs(board, buffer, r, c, m, n, trie, curr_node, result);
                    buffer.pop_back();
                }
            }

        // Return the result
        return result;
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> &board, std::vector<std::string> &words) { return sol1(board, words); }
};