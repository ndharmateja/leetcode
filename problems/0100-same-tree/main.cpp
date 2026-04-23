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

    static bool solution1(TreeNode *p, TreeNode *q)
    {
        // If both are null, we can return true
        // If one of them is null now, then it means that they aren't the same tree
        // In the following if statement, if one of them is null then only both
        // being null will return true
        if (!p || !q)
            return p == q;

        // At this point both trees rooted at p and q are the same
        // then the values in the root's must be same and the subtrees must be same
        // Because && uses short circuiting, at this point if p->val != q->val, we directly
        // return false without making the recursive calls to the subtrees. and same if the
        // left subtrees aren't same, we don't have to check the right subtree.
        return p->val == q->val &&
               solution1(p->left, q->left) &&
               solution1(p->right, q->right);
    }

public:
    bool isSameTree(TreeNode *p, TreeNode *q) { return solution1(p, q); }
};