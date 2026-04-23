#include <vector>

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

    static void inorder_traversal(TreeNode *root, std::vector<int> &result)
    {
        if (!root)
            return;
        inorder_traversal(root->left, result);
        result.push_back(root->val);
        inorder_traversal(root->right, result);
    }

    static int solution1(TreeNode *root, int k)
    {
        std::vector<int> result;
        inorder_traversal(root, result);
        return result[k - 1];
    }

    /**
     * TODO: solve using iterative inorder solution
     */
    static int solution2(TreeNode *root, int k) {}

public:
    int kthSmallest(TreeNode *root, int k) { return solution1(root, k); }
};