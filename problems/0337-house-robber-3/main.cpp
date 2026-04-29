#include <utility>
#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
private:
    /**
     * Recursive function that computes the max sums that can be robbed
     * in the whole tree (including and excluding the root)
     *
     * Theta(n) time and Theta(h) space
     * where n is the number of houses and h is the height of the binary tree
     */
    static std::pair<int, int> compute_max_sums(TreeNode *root)
    {
        // If the root is null, then the max sum including/excluding the root
        // is 0
        if (!root)
            return {0, 0};

        // Recursively find the max sums that can be robbed for each subtree
        // including and excluding the subtrees' roots
        auto [left_including, left_excluding] = compute_max_sums(root->left);
        auto [right_including, right_excluding] = compute_max_sums(root->right);

        // The max sum that can be robbed including the root of the whole tree
        // If we are including the root, then we should exclude the roots of the
        // subtrees
        int max_including = left_excluding + right_excluding + root->val;

        // If we are excluding the root, then we can either include or exclude the roots of the
        // subtrees. So we take max between including and excluding of each subtree
        // and add them up
        int max_excluding = std::max(left_including, left_excluding) + std::max(right_including, right_excluding);

        // We return the max sums (including and excluding the root) for the whole tree
        return {max_including, max_excluding};
    }

    static int solution1(TreeNode *root)
    {
        // We find the max sums robbed including and excluding the root
        // and take the max between them
        auto [max_including, max_excluding] = compute_max_sums(root);
        return std::max(max_including, max_excluding);
    }

public:
    int rob(TreeNode *root) { return solution1(root); }
};