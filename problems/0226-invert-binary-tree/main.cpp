/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:
    TreeNode *invertTree(TreeNode *root)
    {
        // Base case: if tree is empty, return nullptr
        if (!root)
            return root;

        // Store the left node, before assigning the inverted right tree
        // as tree.left
        TreeNode *left = root->left;

        // Invert left subtree and assign it to right
        // and invert right subtree and assign it to left
        root->left = invertTree(root->right);
        root->right = invertTree(left);

        // Return the root
        return root;
    }
};