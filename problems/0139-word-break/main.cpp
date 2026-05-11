#include <string>
#include <vector>
#include <array>
#include <cstdint>

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
public:
    TrieNode *root;
    Trie() : root{new TrieNode()} {}
    ~Trie() { delete root; }

    void insert(const std::string &word)
    {
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
};

class Solution
{
private:
    static bool sol1(const std::string &s,
                     int i, int n,
                     std::vector<int8_t> &memo,
                     const TrieNode *root)
    {
        if (i == n)
            return true;

        int8_t &answer = memo[i];
        if (answer != -1)
            return answer;

        const TrieNode *curr = root;
        answer = 0;
        for (int j = i; j < n; j++)
        {
            curr = curr->children[s[j] - 'a'];
            if (!curr)
            {
                answer = 0;
                break;
            }
            if (curr->is_word && sol1(s, j + 1, n, memo, root))
            {
                answer = 1;
                break;
            }
        }

        return answer;
    }

    static bool sol1(const std::string &s, const std::vector<std::string> &words)
    {
        // Create a trie from all the given words
        Trie trie;
        for (const auto &word : words)
            trie.insert(word);

        int n{static_cast<int>(s.size())};
        std::vector<int8_t> memo(n, -1);
        return sol1(s, 0, n, memo, trie.root);
    }

public:
    bool wordBreak(const std::string &s, const std::vector<std::string> &words) { return sol1(s, words); }
};