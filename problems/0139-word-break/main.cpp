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
private:
    TrieNode *root;

public:
    // ! We are changing this also from the original Trie data structure
    // ! root{new TrieNode()} instead of root{nullptr}
    Trie() : root{new TrieNode()} {}
    ~Trie() { delete root; }

    TrieNode *get_root() { return root; }

    void insert(const std::string &word)
    {
        // ! We don't need this check as we don't have the delete functionality
        // ! like in the original Trie data structure. See the reference for more details.
        // ! https://github.com/ndharmateja/data-structures-cpp/blob/master/data-structures/tries/trie.hpp
        // If root is null (could get null after deletions)
        // we create it
        // if (!root)
        //     root = new TrieNode();

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

/**
 * This enum takes only 1 byte of space as we are using int8_t
 * 0 evaluates to bool value false
 * 1 evaluates to bool value true
 */
enum MemoResult : int8_t
{
    UNCOMPUTED = -1,
    FALSE = 0,
    TRUE = 1
};

class Solution
{
private:
    /**
     * Recursive function that returns true if s[i:] can be segmented properly
     * into a sequence of the words belonging the trie rooted at @param root
     * This function is memoized for the top down DP approach.
     * ! This solutions is faster than an checking if the substring is
     * ! a valid word using an unordered_map (even though we use the leetcode
     * ! constraint that the max word length is 20) for 2 reasons:
     * ! 1. Checking if the curr trie node forms a word is extremely fast (Theta(1) time)
     * !    compared to an unordered_map (it takes time Theta(L) where L is the length
     * !    of the prefix) and the overhead of the hash function computation and
     * !    linked list traversal and a full string compare once we reach the corresponding bucket etc.
     * ! 2. We are pruning the search as soon as we reach a prefix that is not
     * !    part of the trie. We don't have to go further but we wouldn't be able
     * !    to figure that out using an unordered_map.
     */
    static bool sol1(const std::string &s,
                     int i, int s_length,
                     std::vector<MemoResult> &memo,
                     const TrieNode *root)
    {
        // If the i pointer reaches the end of the string
        // this can be trivially segmented. So we return true
        if (i == s_length)
            return true;

        // If memo already contains the result, we can return it
        MemoResult &answer = memo[i];
        if (answer != MemoResult::UNCOMPUTED)
            return answer;

        // We start trying to form a word starting from index 'i'
        // For each 'j' if s[i:j+1] is a valid word in the given trie
        // and if s[j+1:] can be broken down properly (which we can check recursively)
        // then we can return true
        //
        // We keep moving the TrieNode step by step to check if that is a valid word
        // and also to check if that prefix is valid
        //
        // At any point if curr becomes null, it means that we don't have any words
        // with the prefix s[i:j+1], so we can stop traversing this path
        // and directly return false
        //
        // We start with a default value of false as the result
        // and then if we could actually find a valid break, we can change it to true
        // and when we are setting answer=False we are directly setting memo[i]
        // as answer is a reference to memo[i]
        const TrieNode *curr = root;
        answer = MemoResult::FALSE;

        // For each j, we see if s[i:j+1] is a valid word and if s[j+1:] can be broken down
        // properly recursively
        for (int j = i; j < s_length; j++)
        {
            // We update the curr node so that curr represents the string s[i:j+1]
            curr = curr->children[s[j] - 'a'];

            // If curr becomes null, then the prefix s[i:j+1] doesn't even exist in the trie
            // so we don't need to move further as we can't break down s[i:]
            // We would have already returned true if we could have broken down for one of
            // the previous js
            if (!curr)
                break;

            // If s[i:j+1] is a valid word and if s[j+1:] can be broken down properly
            // we can return true
            // We don't need to check further j values
            if (curr->is_word && sol1(s, j + 1, s_length, memo, root))
            {
                answer = MemoResult::TRUE;
                break;
            }
        }

        // FALSE = 0 in the MemoResult evaluates to bool value false
        // TRUE = 1 in the MemoResult evaluates to bool value true
        // answer can't be UNCOMPUTED at this point
        return answer;
    }

    /**
     * Top down DP solution
     */
    static bool sol1(const std::string &s, const std::vector<std::string> &words)
    {
        // Create a trie from all the given words
        Trie trie;
        for (const auto &word : words)
            trie.insert(word);

        // Call the recursive function to check if s[0:] can be broken down properly
        int s_length{static_cast<int>(s.size())};
        std::vector<MemoResult> memo(s_length, MemoResult::UNCOMPUTED);
        return sol1(s, 0, s_length, memo, trie.get_root());
    }

public:
    bool wordBreak(const std::string &s, const std::vector<std::string> &words) { return sol1(s, words); }
};