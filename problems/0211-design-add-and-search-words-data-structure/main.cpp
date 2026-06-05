#include <string>
#include <array>

/**
 * See problem 208 for more details
 */

struct TrieNode
{
    bool is_word{false};
    std::array<TrieNode *, 26> children{};

    ~TrieNode()
    {
        for (auto ptr : children)
            delete ptr;
    }
};

class WordDictionary
{
private:
    TrieNode *root;

    /**
     * Recursive function that looks for pattern[idx:] starting at the trie node curr
     * Assumes that curr is not nullptr (we only call it if curr is not null)
     *
     * Invariants:
     * 1. curr is not null
     * 2. curr node corresponds the pattern[:idx] prefix
     */
    static bool search(TrieNode *curr, const std::string &pattern, int idx, int pattern_length)
    {
        // Base cases
        // ! We can skip this base case to prevent an extra function call when curr is nullptr
        // ! by making the check before calling the function itself
        // If curr ptr is nullptr, it means that we have reached a deadend
        // so we can immediately return false
        // if (!curr)
        //     return false;

        // If we have reached the end of the pattern, then idx will be equal to pattern_length
        // (and not pattern_length-1) as the root node is the first node checked when idx=0
        // Once we reach a trie node with k chars, then idx would be k
        // Once we reach the trie node that represents the given pattern
        // we can return true if this node represents a full pattern
        if (idx == pattern_length)
            return curr->is_word;

        // If idx hasn't reached pattern_length yet, we are in the middle of the pattern search
        // so we search for the pattern in all its children
        // If the current char is "." we search this char as a wild card
        // and search among all its children
        unsigned char c = pattern[idx];
        if (c == '.')
        {
            // Along any branch if search returns true, we can immediately return
            // true for an early exit
            for (auto child_ptr : curr->children)
                if (child_ptr)
                    if (search(child_ptr, pattern, idx + 1, pattern_length))
                        return true;

            // If we reach here, then search is fruitless along this path
            return false;
        }

        // If the char is not a '.' we can search along that specific child
        auto child_ptr = curr->children[c - 'a'];
        return child_ptr
                   ? search(child_ptr, pattern, idx + 1, pattern_length)
                   : false;
    }

public:
    WordDictionary() : root{new TrieNode()} {}
    ~WordDictionary() { delete root; }

    void addWord(const std::string &word)
    {
        // Traverse along the trie following each character
        // and insert new nodes along the path if there aren't any
        int n{static_cast<int>(word.size())}, idx;
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

    bool search(const std::string &pattern) { return search(root, pattern, 0, static_cast<int>(pattern.size())); }
};