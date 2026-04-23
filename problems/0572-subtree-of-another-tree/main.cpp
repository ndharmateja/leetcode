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

    /**
     * Checkout problem 100 for more details
     */
    static bool is_same_tree(TreeNode *p, TreeNode *q)
    {
        if (!p || !q)
            return p == q;
        return p->val == q->val &&
               is_same_tree(p->left, q->left) &&
               is_same_tree(p->right, q->right);
    }

    /**
     * Recursive function that tells if the tree rooted at sub_root is a subtree
     * of the tree rooted at root
     */
    static bool solution1(TreeNode *root, TreeNode *sub_root)
    {
        // If both root and subtree are true then it is trivially true
        if (!root && !sub_root)
            return true;

        // If only root is null (at this point since both aren't null, sub_root is not null)
        // then we can return false because a non-null tree can't be the subtree of a null tree
        if (!root)
            return false;

        // If only the sub_root tree is null, then it is trivially a subtree of the
        // non-null tree
        if (!sub_root)
            return true;

        // If the trees rooted at root and sub_root are same then it is a subtree
        if (is_same_tree(root, sub_root))
            return true;

        // If both aren't the same tree
        // we check if the sub_root tree is a subtree of either the left or right subtrees
        // Short circuiting => if the sub_root is a subtree of the left subtree
        // we return true immediately
        return solution1(root->left, sub_root) || solution1(root->right, sub_root);
    }

    /**
     * Recursive function that tells if the tree rooted at sub_root is a subtree
     * of the tree rooted at root
     * A cleaner version of solution1 as is_same_tree does the null checks
     */
    static bool solution2(TreeNode *root, TreeNode *sub_root)
    {
        // If root is null, it means we have exhausted and we haven't found a match
        // sub_root is non null according to the constraints
        if (!root)
            return false;

        // Short circuiting
        return is_same_tree(root, sub_root) ||
               solution2(root->left, sub_root) ||
               solution2(root->right, sub_root);
    }

    /**
     * TODO: Serialize both trees and do a substring search algorithm
     */
    static bool solution3(TreeNode *root, TreeNode *sub_root) { return false; }

public:
    bool isSubtree(TreeNode *root, TreeNode *sub_root) { return solution2(root, sub_root); }
};