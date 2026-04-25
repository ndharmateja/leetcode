#include <string>
#include <stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * The deserialization works in linear time as it goes just forward
 * in one pass.
 */
namespace Solution2
{
    class Codec
    {
    private:
        /**
         * Recursively serializes the tree rooted at root according to preorder
         * traversal. We use empty brackets for empty children as otherwise we
         * wouldn't know if it is the left/right child when there is only one child
         *
         * Eg: If the tree is
         *       A
         *      / \
         *     B   C
         *    / \
         *   D   E
         * Then the serialized string would be: A(B(D()())(E()()))(C())
         */
        static void serialize(TreeNode *root, std::string &result)
        {
            // If the root is nullptr, then nothing to add to the string
            if (!root)
                return;

            // Since it is preorder, we first append the value of the root
            result.append(std::to_string(root->val));

            // We append the serialized string (which is recursively computed)
            // of the left subtree (could be potentially nullptr in which case empty string)
            // between paranthesis
            result.push_back('(');
            serialize(root->left, result);
            result.push_back(')');

            // We do the same for the right subtree
            result.push_back('(');
            serialize(root->right, result);
            result.push_back(')');
        }

        /**
         * Parses the integer in the data string starting at index i
         * Makes i the index after the number part ends
         * Also parses negative values
         *
         * Eg:
         *     i
         *     ↓
         *  ...-125...
         * parses and returns -125 as the answer and makes i point to the index after -125
         *        i
         *        ↓
         * ...-125...
         */
        static int parse_integer(const std::string &data, int &i)
        {
            // Error checking. The character at should either be an int or a '-' char
            unsigned char c = data[i];
            if (!std::isdigit(c) && c != '-')
                throw std::runtime_error("Invalid input");

            // Handle negative values
            bool is_negative = false;
            if (c == '-')
            {
                is_negative = true;
                i++;
            }

            // Parse the number using Horner's method
            int result = 0;
            while (std::isdigit(c = data[i]))
            {
                result = (result * 10) + (c - '0');
                i++;
            }

            // At this point, i will point to the first character after the number ends
            // If is_negative is true, we flip the sign of the result
            return is_negative ? -result : result;
        }

        /**
         * Recursive function that deserializes a tree starting at index i
         * Makes i point to the after the subtree rooted at the value starting at index 'i'
         *
         *       2              17
         *       ↓              ↓
         * Eg: A(B(D()())(E()()))(C())
         * is the tree
         *       A
         *      / \
         *     B   C
         *    / \
         *   D   E
         *
         * If we call deserialize(data, 2)
         * we need to parse the tree rooted at B
         * and this function makes i point to 17 which is the closing parenthesis
         * after the tree string of B ends
         */
        static TreeNode *deserialize(const std::string &data, int &i)
        {
            // If the char at 'i' is ')' it means that there is the empty paranthesis of the empty node
            // so we can return nullptr
            unsigned char c = data[i];
            if (c == ')')
                return nullptr;

            // Parse the integer starting at index 'start'
            int root_val = parse_integer(data, i);

            // Create the root node
            TreeNode *root = new TreeNode(root_val);

            // At this point i points to the closing paranthesis outside the left subtree
            //     i
            //     ↓
            // root(left-subtree)(right-subtree)
            // So we increment 'i' to be able to pass it to the recursive call to parse
            // the left subtree
            i++;

            // Parse the left subtree
            root->left = deserialize(data, i);

            // At this point i points to the closing paranthesis outside the left subtree
            //                  i
            //                  ↓
            // root(left-subtree)(right-subtree)
            // so we increment it twice to point to the start of the subtree string of the right subtree
            i += 2;

            // Parse the right subtree
            root->right = deserialize(data, i);

            // At this point i points to the closing paranthesis outside the right subtree
            //                                 i
            //                                 ↓
            // root(left-subtree)(right-subtree)
            // but according to the recursive function contract, i should point to the index
            // after the tree rooted at root ends. so we increment 'i'
            i++;

            // Return the parsed tree
            return root;
        }

    public:
        // Encodes a tree to a single string.
        std::string serialize(TreeNode *root)
        {
            std::string result;
            serialize(root, result);
            return result;
        }

        // Decodes your encoded data to tree.
        TreeNode *deserialize(const std::string &data)
        {
            // Empty string case
            if (data.empty())
                return nullptr;

            // Parse the non-empty tree
            int i = 0;
            return deserialize(data, i);
        }
    };
}

/**
 * Deserialization works in n^2 time as it first finds the corresponding
 * closing paranthesis of the opening bracket and deserializes everything
 * in between
 */
namespace Solution1
{
    class Codec
    {
    private:
        /**
         * Recursively serializes the tree rooted at root according to preorder
         * traversal. We use empty brackets for empty children as otherwise we
         * wouldn't know if it is the left/right child when there is only one child
         *
         * Eg: If the tree is
         *       A
         *      / \
         *     B   C
         *    / \
         *   D   E
         * Then the serialized string would be: A(B(D()())(E()()))(C())
         */
        static void serialize(TreeNode *root, std::string &result)
        {
            // If the root is nullptr, then nothing to add to the string
            if (!root)
                return;

            // Since it is preorder, we first append the value of the root
            result.append(std::to_string(root->val));

            // We append the serialized string (which is recursively computed)
            // of the left subtree (could be potentially nullptr in which case empty string)
            // between paranthesis
            result.push_back('(');
            serialize(root->left, result);
            result.push_back(')');

            // We do the same for the right subtree
            result.push_back('(');
            serialize(root->right, result);
            result.push_back(')');
        }

        static bool is_opening(char c) { return c == '('; }
        static bool is_closing(char c) { return c == ')'; }

        static int find_closing_paranthesis(const std::string &data, int start_at)
        {
            // Using this integer instead of an actual stack improved the performance
            // from 5-6% to around 22-23%
            int balance = 0;
            int i = start_at;
            while (true)
            {
                char c = data[i];
                if (is_opening(c))
                {
                    balance++;
                }
                else if (is_closing(c))
                {
                    balance--;
                    if (!balance)
                        return i;
                }
                i++;
            }

            // We will never reach here
            return -1;
        }

        static TreeNode *deserialize(const std::string &data, int start, int end)
        {
            if (start > end)
                return nullptr;

            // Accumulate the value of the root using Horner's method
            int root_val = 0;
            int i = start;
            bool is_root_val_negative = data[start] == '-';
            if (is_root_val_negative)
                i++;

            unsigned char c;
            while (std::isdigit(c = data[i]))
            {
                root_val = (root_val * 10) + (c - '0');
                i++;
            }
            if (is_root_val_negative)
                root_val = -root_val;

            // Create the root node
            TreeNode *root = new TreeNode(root_val);

            // At this point if i crosses end, it means that there are no subtree children
            if (i > end)
                return root;

            // Find the closing bracket corresponding to the opening paranthesis at 'i'
            // and deserialize the left subtree
            int left_closing_index = find_closing_paranthesis(data, i);
            root->left = deserialize(data, i + 1, left_closing_index - 1);

            // Update i for the right subtree
            i = left_closing_index + 1;

            // At this point if i crosses end, it means that there is no right subtree child
            if (i > end)
                return root;

            // Deserialize the right subtree and return the root
            int right_closing_index = find_closing_paranthesis(data, i);
            root->right = deserialize(data, i + 1, right_closing_index - 1);
            return root;
        }

    public:
        // Encodes a tree to a single string.
        std::string serialize(TreeNode *root)
        {
            std::string result;
            serialize(root, result);
            return result;
        }

        // Decodes your encoded data to tree.
        TreeNode *deserialize(const std::string &data) { return deserialize(data, 0, data.size() - 1); }
    };
}
