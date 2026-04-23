#include <vector>
#include <unordered_map>

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

    static TreeNode *solution1(const std::vector<int> &preorder, int pre_l, int pre_r,
                               const std::vector<int> &inorder, int in_l, int in_r,
                               const std::unordered_map<int, int> &values_to_idx_map)
    {
        // If no elements in this range
        if (pre_l > pre_r)
            return nullptr;

        // At any point #nodes in the preorder range (pre_r - pre_l + 1) would be same as
        // the #nodes in the inorder range (in_r - in_l + 1)
        // If the range has just one element we directly create the node out of that element
        // The root of the tree for the current range is going to be preorder[pre_l]
        int root_val = preorder[pre_l];
        TreeNode *root = new TreeNode(root_val);
        if (pre_l == pre_r)
            return root;

        // Find the root's index in the inorder range (guaranteed to exist)
        // To make this lookup faster, we use the unordered map mapped from the values to the index
        int root_index_inorder = values_to_idx_map.at(root_val);

        // Build the left and right subtrees recursively
        int num_nodes_in_left_subtree = root_index_inorder - in_l;
        int num_nodes_in_right_subtree = in_r - root_index_inorder;
        root->left = solution1(preorder, pre_l + 1, pre_l + 1 + num_nodes_in_left_subtree - 1,
                               inorder, in_l, root_index_inorder - 1,
                               values_to_idx_map);
        root->right = solution1(preorder, pre_r - num_nodes_in_right_subtree + 1, pre_r,
                                inorder, root_index_inorder + 1, in_r,
                                values_to_idx_map);

        // Return the root
        return root;
    }

    static TreeNode *solution1(const std::vector<int> &preorder, const std::vector<int> &inorder)
    {
        size_t n{preorder.size()};
        if (!n)
            return nullptr;

        // Build a values to index map from the inorder values to find the index quickly
        // Optimization: Since the values are going to be in the [-3000, 3000] range
        // we could use a vector instead of this map too
        std::unordered_map<int, int> values_to_idx_map;
        for (int i = 0; i < n; i++)
            values_to_idx_map.emplace(inorder[i], i);

        return solution1(preorder, 0, n - 1, inorder, 0, n - 1, values_to_idx_map);
    }

public:
    /**
     * Constraints:
     *  1 <= preorder.length <= 3000
     *  inorder.length == preorder.length
     *  -3000 <= preorder[i], inorder[i] <= 3000
     *  preorder and inorder consist of unique values.
     *  Each value of inorder also appears in preorder.
     *  preorder is guaranteed to be the preorder traversal of the tree.
     *  inorder is guaranteed to be the inorder traversal of the tree.
     */
    TreeNode *buildTree(const std::vector<int> &preorder, const std::vector<int> &inorder) { return solution1(preorder, inorder); }
};