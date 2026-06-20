#include <utility>
#include <algorithm>
#include <limits>

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
    static inline const int neg_inf = std::numeric_limits<int>::min();

    /**
     * To avoid overflows, returns negative infinity if any of the values is negative infinity
     * otherwise returns the sum
     */
    static int sum(int x, int y, int z = 0)
    {
        if (x == neg_inf || y == neg_inf || z == neg_inf)
            return neg_inf;
        return x + y + z;
    }

    /**
     * Finds the pair of the max sum ending at the root and the max sum
     * not ending at the root for the tree rooted at root
     */
    static std::pair<int, int> find_max_sums(const TreeNode *root)
    {
        // Base case
        if (!root)
            return {neg_inf, neg_inf};

        // Recursively find sums of left and right subtrees
        auto [left_max_sum_ending_at_root, left_max_sum_not_ending_at_root] = find_max_sums(root->left);
        auto [right_max_sum_ending_at_root, right_max_sum_not_ending_at_root] = find_max_sums(root->right);

        // Find the max sum ending at root
        int max_sum_ending_at_root = std::max({root->val,
                                               sum(root->val, left_max_sum_ending_at_root),
                                               sum(root->val, right_max_sum_ending_at_root)});

        // Find the max sum not ending at root
        int max_sum_not_ending_at_root = std::max({left_max_sum_ending_at_root,
                                                   right_max_sum_ending_at_root,
                                                   left_max_sum_not_ending_at_root,
                                                   right_max_sum_not_ending_at_root,
                                                   sum(root->val, left_max_sum_ending_at_root, right_max_sum_ending_at_root)});

        // Return the pair of max sum ending at the root and the max sum
        // not ending at the root
        return {max_sum_ending_at_root, max_sum_not_ending_at_root};
    }

    static int sol1(const TreeNode *root)
    {
        auto [max_sum_ending_at_root, max_sum_not_ending_at_root] = find_max_sums(root);
        return std::max(max_sum_ending_at_root, max_sum_not_ending_at_root);
    }

    /**
     * Returns the max path sum *ending* at root.
     * Also updates the global_max with the value of the max path sum overall (not
     * necessarily ending at the root).
     */
    static int explore(const TreeNode *root, int &global_max)
    {
        // Base case: If the root is null, then the max path sum ending at root is 0
        // and we need not update the global_max
        if (!root)
            return 0;

        // When we call explore on the left child, global_max gets updated with
        // the max path sum from the left subtree and also the max path sum that
        // ends at the left child (in the left subtree) is returned
        // Similarly with the right subtree
        int left_max_sum_ending_at_root = explore(root->left, global_max);
        int right_max_sum_ending_at_root = explore(root->right, global_max);
        int left_gain = std::max(left_max_sum_ending_at_root, 0);
        int right_gain = std::max(right_max_sum_ending_at_root, 0);

        // For the max path sum that passes through the root, we only consider the left
        // and right results if they are positive, but we have to include the root
        // This sum could just contain the root
        // Note that if the max path sum for the tree rooted at root doesn't pass through
        // the root, they are already taken care of in the calls to explore on left
        // and right subtrees
        int max_path_sum_passing_through_root = root->val + left_gain + right_gain;
        global_max = std::max(global_max, max_path_sum_passing_through_root);

        // According to the recursive contract, we need to return the max path sum
        // ending at the root, so we pick the max of the left and the right results (if positive)
        // and add it to the root's value
        return root->val + std::max(left_gain, right_gain);
    }

    static int sol2(const TreeNode *root)
    {
        int global_max = std::numeric_limits<int>::min();
        explore(root, global_max);
        return global_max;
    }

public:
    int maxPathSum(const TreeNode *root) { return sol2(root); }
};