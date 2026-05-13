#include <vector>
#include <string>
#include <utility>
#include <array>

struct TrieNode
{
    bool is_word;
    std::array<TrieNode *, 26> children;
    TrieNode() : is_word{false}
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
    TrieNode *remove(TrieNode *node, const std::string &word, int d)
    {
        if (!node)
            return nullptr;
        if (d == static_cast<int>(word.size()))
            node->is_word = false;
        else
        {
            unsigned char c = word[d];
            node->children[c - 'a'] = remove(node->children[c - 'a'], word, d + 1);
        }

        if (node->is_word)
            return node;
        for (int i = 0; i < 26; i++)
            if (node->children[i])
                return node;

        delete node;
        return nullptr;
    }

public:
    TrieNode *root;

    Trie() : root{nullptr} {}
    ~Trie() { delete root; }

    void insert(const std::string &word)
    {
        // If root is null (could get null after deletions)
        // we create it
        if (!root)
            root = new TrieNode();

        // Traverse along the trie following each character
        // and insert new nodes along the path if there aren't any
        int idx;
        TrieNode *curr{root};
        for (unsigned char c : word)
        {
            // We use the reference to the child as we can get away only with one array access
            // instead of potentially three array accesses
            idx = c - 'a';
            TrieNode *&child = curr->children[idx];
            if (!child)
                child = new TrieNode();

            // Update the curr pointer
            curr = child;
        }

        // At this point the trie node corresponds the given word
        // Whether or not it was already there, at this point this node
        // represents a full word, so we mark the is_word to be true
        curr->is_word = true;
    }

    bool startsWith(const std::string &prefix)
    {
        // If root is null then we can return false
        if (!root)
            return false;

        // Traverse along the trie following the characters
        int idx;
        TrieNode *curr{root};
        for (unsigned char c : prefix)
        {
            // Check if the ith char in the string exists as a key in the
            // children of the curr node
            // If it doesn't exist, we can immediately return false
            // We keep continuing until we reach the last char
            idx = c - 'a';
            curr = curr->children[idx];
            if (!curr)
                return false;
        }

        // At this point we know the trie node corresponding to the prefix exists
        // as we'd have returned false otherwise
        // We can directly return true
        return true;
    }

    void remove(const std::string &word) { root = remove(root, word, 0); }
};

class Solution
{
private:
    static inline const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Assumes that node is not null. So we have to check before calling.
     */
    static void dfs(const std::vector<std::vector<char>> &board, std::string &curr_word,
                    int r, int c, int m, int n,
                    Trie &trie,
                    TrieNode *curr_node, std::vector<std::vector<bool>> &visited,
                    std::vector<std::string> &result)
    {
        // If this node is a full word, then we have found a word on the board
        // We can remove this word from the trie as we don't want to find
        // duplicates of the same word and removing found words prunes the search
        // space on the board
        if (curr_node->is_word)
        {
            result.push_back(curr_word);
            curr_node->is_word = false;
        }

        // Mark this cell as visited so that we don't use this as part of further words
        // Visit all the unvisited neighbours that are part of the trie path
        visited[r][c] = true;
        for (const auto &[dr, dc] : directions)
        {
            int new_r = r + dr;
            int new_c = c + dc;
            if (new_r < 0 || m <= new_r)
                continue;
            if (new_c < 0 || n <= new_c)
                continue;

            unsigned char child_char = board[new_r][new_c];
            TrieNode *child_node = curr_node->children[child_char - 'a'];
            if (!visited[new_r][new_c] &&
                child_node)
            {
                curr_word.push_back(child_char);
                dfs(board, curr_word, new_r, new_c, m, n, trie, child_node, visited, result);
                curr_word.pop_back();
            }
        }

        // Unmark this cell as visited
        visited[r][c] = false;
    }

    static std::vector<std::string> sol1(
        const std::vector<std::vector<char>> &board,
        const std::vector<std::string> &words)
    {
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
        std::string curr_word;
        curr_word.reserve(max_word_length);
        std::vector<std::string> result;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int r = 0; r < m && trie.root; r++)
            for (int c = 0; c < n && trie.root; c++)
            {
                unsigned char ch = board[r][c];
                TrieNode *curr_node = trie.root;
                curr_node = curr_node->children[ch - 'a'];
                if (curr_node)
                {
                    curr_word.push_back(ch);
                    dfs(board, curr_word, r, c, m, n, trie, curr_node, visited, result);
                    curr_word.pop_back();
                }
            }

        // Return the result
        return result;
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> &board, std::vector<std::string> &words) { return sol1(board, words); }
};