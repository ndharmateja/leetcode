class Solution
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    static TreeNode *solution1(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // Find the first diverging point while looking for both p and q
        // and that node is the lowest common ancestor
        TreeNode *curr = root;
        while (true)
        {
            // If p and q both are in the left subtree or if both of them
            // are in the right subtree then curr is not the diverging point
            if (p->val < curr->val && q->val < curr->val)
                curr = curr->left;
            else if (p->val > curr->val && q->val > curr->val)
                curr = curr->right;

            // In this case (either p and q are on opposite sides or if p or q's value equals curr's value)
            // curr itself is the diverging point and therefore the lowest common ancestor
            else
                return curr;
        }

        // We will never reach here as there is a guaranteed solution
        return nullptr;
    }

    /**
     * Recursive solution to find the lowest common ancestor
     */
    static TreeNode *solution2(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // If both p and q are in the left subtree of the root then the lowest
        // common ancestor is in the left subtree
        if (p->val < root->val && q->val < root->val)
            return solution2(root->left, p, q);

        // If both p and q are in the right subtree of the root then the lowest
        // common ancestor is in the right subtree
        else if (p->val > root->val && q->val > root->val)
            return solution2(root->right, p, q);

        // If it is the case that either p's value or q's value matches the root's value
        // or if it is the case that p and q are on the opposite sides of the root
        // then this root itself is the lowest common ancestor
        return root;
    }

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) { return solution1(root, p, q); }
};