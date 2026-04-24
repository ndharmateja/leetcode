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

    static int solution1(TreeNode *root, int max_so_far)
    {
        // If there is no tree, then the number of good nodes is 0
        if (!root)
            return 0;

        // If the root's value is greater than the maximum so far along from the original root
        // to the subtree's root, then the subtree root is a good node
        // and its value can be considered as the new max_along path to root
        int count = 0;
        if (root->val >= max_so_far)
        {
            count = 1;
            max_so_far = root->val;
        }
        // And we compute the total #good nodes in the subtree by recursively calling it on
        // the left and right subtrees
        return count + solution1(root->left, max_so_far) + solution1(root->right, max_so_far);
    }

    static int solution1(TreeNode *root) { return solution1(root, std::numeric_limits<int>::min()); }

public:
    int goodNodes(TreeNode *root) { return solution1(root); }
};