#include <string>
#include <unordered_map>
#include <array>

/**
 * This solution uses unordered map for storing the children of trie nodes
 * for a trie node
 */
namespace Solution1
{
    struct TrieNode
    {
        bool is_word;
        std::unordered_map<unsigned char, TrieNode *> children;
        TrieNode() : is_word{false} {}

        // Recursive destructor that deletes each of its children
        ~TrieNode()
        {
            for (auto &pair : children)
                delete pair.second;
        }
    };

    class Trie
    {
    private:
        TrieNode *root;

    public:
        Trie() : root{new TrieNode()} {}
        ~Trie() { delete root; }

        void insert(const std::string &word)
        {
            // Traverse along the trie following each character
            // and insert new nodes along the path if there aren't any
            TrieNode *curr{root};
            for (unsigned char c : word)
            {
                // Try inserting the key first and if insertion happens we can assign a new node
                // otherwise we don't need to do anything and just update the curr pointer
                // This lets us get away with just one hash function call
                auto [it, inserted] = curr->children.try_emplace(c, nullptr);

                // If inserted for the first time, we create the corresponding TrieNode
                if (inserted)
                    it->second = new TrieNode();

                // Update the curr pointer
                curr = it->second;
            }

            // At this point the trie node corresponds the given word
            // Whether or not it was already there, at this point this node
            // represents a full word, so we mark the is_word to be true
            curr->is_word = true;
        }

        bool search(const std::string &word)
        {
            // Traverse along the trie following the characters
            TrieNode *curr{root};
            for (unsigned char c : word)
            {
                // Check if the ith char in the string exists as a key in the
                // children of the curr node
                // If it doesn't exist, we can immediately return false
                auto it = curr->children.find(c);
                if (it == curr->children.end())
                    return false;

                // We keep continuing until we reach the last char
                curr = it->second;
            }

            // Say the word is EAT and all intermediate trienodes exist along the path
            // At this point curr will point to the node forming EAT
            // so if this node represents a full word, we can return true
            // false otherwise
            return curr->is_word;
        }

        bool startsWith(const std::string &prefix)
        {
            // This is very similar to search but the final result need not be a full word
            // So if there is a path to the given prefix we can return true
            // Traverse along the trie following the characters
            TrieNode *curr{root};
            for (unsigned char c : prefix)
            {
                // Check if the ith char in the string exists as a key in the
                // children of the curr node
                // If it doesn't exist, we can immediately return false
                auto it = curr->children.find(c);
                if (it == curr->children.end())
                    return false;

                // We keep continuing until we reach the last char
                curr = it->second;
            }

            // At this point we know the trie node corresponding to the prefix exists
            // as we'd have returned false otherwise
            // We can directly return true
            return true;
        }
    };
};

/**
 * This solution is very similar to solution 1 except
 * we use an array of size 26 for the children of each trie node
 * as only lowercase english alphabets are present according to
 * LeetCode constraints
 * Better cache locality
 */
namespace Solution2
{
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

        bool search(const std::string &word)
        {
            // Traverse along the trie following the characters
            int idx;
            TrieNode *curr{root};
            for (unsigned char c : word)
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

            // Say the word is EAT and all intermediate trienodes exist along the path
            // At this point curr will point to the node forming EAT
            // so if this node represents a full word, we can return true
            // false otherwise
            return curr->is_word;
        }

        bool startsWith(const std::string &prefix)
        {
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
    };
};