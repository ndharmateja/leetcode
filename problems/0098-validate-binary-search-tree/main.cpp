#include <limits>

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

    static bool solution1(TreeNode *root, long long min, long long max)
    {
        // If no node, it is trivially true
        if (!root)
            return true;

        // We are using long long datatype to avoid overflow errors
        // Otherwise we check if root's value is in the range [min, max]
        // and the left subtree values are in the range [int_min, root->val-1]
        // and the right subtree values are in the range [root->val+1, int_max]
        return (min <= root->val && root->val <= max) &&
               solution1(root->left, min, static_cast<long long>(root->val) - 1) &&
               solution1(root->right, static_cast<long long>(root->val) + 1, max);
    }

    static bool solution1(TreeNode *root)
    {
        long long min_int = std::numeric_limits<long long>::min();
        long long max_int = std::numeric_limits<long long>::max();
        return solution1(root, min_int, max_int);
    }

public:
    bool isValidBST(TreeNode *root) { return solution1(root); }
};
