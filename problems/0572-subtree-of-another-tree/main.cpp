#include <string>

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
     * Recursively serializes the tree rooted at root according to preorder
     * traversal. We use empty brackets for empty children as otherwise we
     * wouldn't know if it is the left/right child when there is only one child
     *
     * See problem 297 for more details. There we didn't use paranthesis around the root value.
     *
     * Eg: If the tree is
     *       A
     *      / \
     *     B   C
     *    / \
     *   D   E
     * Then the serialized string would be: (A)((B)((D)()())((E)()()))((C)())
     */
    static void serialize(TreeNode *root, std::string &result)
    {
        // If the root is nullptr, then nothing to add to the string
        if (!root)
            return;

        // Since it is preorder, we first append the value of the root
        // We also add the parenthesis around the root value
        // to avoid issues with 12()() and 2()() even though 2()() isn't a subtree
        // of 12()(), it is a substring
        result.push_back('(');
        result.append(std::to_string(root->val));
        result.push_back(')');

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

    static std::string serialize(TreeNode *root)
    {
        std::string result;
        serialize(root, result);
        return result;
    }

    /**
     * TODO: Use a linear substring search algo like KMP or Rabin-Karp or Boyer-Moore etc
     */
    static bool is_substring(std::string &s1, std::string &s2) { return s1.find(s2) != std::string::npos; }

    /**
     * Serialize both trees and do a substring search algorithm
     */
    static bool solution3(TreeNode *root, TreeNode *sub_root)
    {
        std::string tree_string = serialize(root);
        std::string subtree_string = serialize(sub_root);
        return is_substring(tree_string, subtree_string);
    }

    /**
     * TODO: Merkle Hashing: Pre-calculate a hash for every node in the sub_root tree based on its value and its children's hashes
     */
    static bool solution4(TreeNode *root, TreeNode *sub_root) { return false; }

public:
    bool isSubtree(TreeNode *root, TreeNode *sub_root) { return solution3(root, sub_root); }
};