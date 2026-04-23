#include <utility>
#include <algorithm>

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
     * Theta(n) time and Theta(h) space complexity (for recursion) in the worst case
     * where n = #nodes and h = height of the tree
     *
     * It is Omega(h) and O(n) in the general case as we can exit early
     */
    static std::pair<int, bool> find_height_and_is_balanced(TreeNode *root)
    {
        // Base case
        if (!root)
            return {-1, true};

        // General case
        // Get the left subtree's height and see if it is balanced
        // If the left subtree itself is not balanced, then we can return false
        // without having to check the right subtree
        // So the height we return is irrelevant
        auto [left_height, left_is_balanced] = find_height_and_is_balanced(root->left);
        if (!left_is_balanced)
            return {-1, false};

        // Same with right subtree
        auto [right_height, right_is_balanced] = find_height_and_is_balanced(root->right);
        if (!right_is_balanced)
            return {-1, false};

        // At this point both subtrees are balanced
        // so at this level it is balanced if the difference in heights is <= 1
        int height = std::max(left_height, right_height) + 1;
        bool is_balanced = std::abs(left_height - right_height) <= 1;
        return {height, is_balanced};
    }

    static bool solution1(TreeNode *root) { return find_height_and_is_balanced(root).second; }

public:
    bool isBalanced(TreeNode *root) { return solution1(root); }
};