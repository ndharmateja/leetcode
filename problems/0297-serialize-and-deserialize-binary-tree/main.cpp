#include <string>
#include <stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

namespace Solution1
{
    class Codec
    {
    private:
        static void serialize(TreeNode *root, std::string &result)
        {
            if (!root)
                return;

            result.append(std::to_string(root->val));

            result.push_back('(');
            serialize(root->left, result);
            result.push_back(')');

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
            // TODO: into a separate function
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

            // TODO: Linearly parse it without having to first find the end
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
