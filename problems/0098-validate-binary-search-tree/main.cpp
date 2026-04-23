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

    static bool solution2(TreeNode *root, int min, int max)
    {
        // If no node, it is trivially true
        if (!root)
            return true;

        // First check if the root's value is in [min, max]
        if (root->val < min || root->val > max)
            return false;

        // At this point, root's value is in [min, max]
        // If the root's value is already min and has a left child we can
        // directly return false as we know that all the values in the tree
        // are unique
        // Similarly for the right side
        if (root->val == min && root->left)
            return false;
        if (root->val == max && root->right)
            return false;

        // Check if the left subtree and the right subtree are in the valid range
        // only if they exist
        // We won't get an overflow issue as we already considered the case
        // where the left child exists and the value of the root itself is min
        // and also we are checking if the root's left exists
        if (root->left && !solution2(root->left, min, root->val - 1))
            return false;
        if (root->right && !solution2(root->right, root->val + 1, max))
            return false;

        // Return the accumulated result
        return true;
    }

    static bool solution2(TreeNode *root)
    {
        int min_int = std::numeric_limits<int>::min();
        int max_int = std::numeric_limits<int>::max();
        return solution2(root, min_int, max_int);
    }
public:
    bool isValidBST(TreeNode *root) { return solution1(root); }
};
