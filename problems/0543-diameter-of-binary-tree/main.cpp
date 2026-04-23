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
     * Theta(n) time and Theta(h) space complexity (for recursion)
     * where n = #nodes, h = height of the tree
     */
    static std::pair<int, int> find_height_and_diameter(TreeNode *root)
    {
        // If root is null, then the height is -1 and the diameter is 0
        if (!root)
            return {-1, 0};

        // The diameter of the tree is either:
        // 1. completely contained in the left subtree (we can get it recursively)
        // 2. completely contained in the right subtree (we can get it recursively)
        // 3. passes through the root (diameter = sum of heights of subtrees + 2)
        // The height of the tree is: the max between the heights of the subtrees + 1
        auto [left_height, left_diameter] = find_height_and_diameter(root->left);
        auto [right_height, right_diameter] = find_height_and_diameter(root->right);
        int height = std::max(left_height, right_height) + 1;
        int diameter = std::max({left_diameter, right_diameter, left_height + right_height + 2});
        return {height, diameter};
    }

    static int solution1(TreeNode *root) { return find_height_and_diameter(root).second; }

public:
    int diameterOfBinaryTree(TreeNode *root) { return solution1(root); }
};