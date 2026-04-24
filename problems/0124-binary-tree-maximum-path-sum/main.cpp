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
     * returns negative infinity if any of the values is negative infinity
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
    static std::pair<int, int> find_max_sums(TreeNode *root)
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

    static int solution1(TreeNode *root)
    {
        auto [max_sum_ending_at_root, max_sum_not_ending_at_root] = find_max_sums(root);
        return std::max(max_sum_ending_at_root, max_sum_not_ending_at_root);
    }

    /**
     * TODO: solve by returning only the single path sum (the one that can extend to a parent)
     * and updating a member variable for the global maximum.
     * TODO: code copied from gemini. understand and refactor it.
     */
    int global_max = std::numeric_limits<int>::min();
    int dfs(TreeNode *root)
    {

        if (!root)
            return 0;

        // Only add positive gains; if a subtree returns a negative sum, ignore it (0)
        int left_gain = std::max(dfs(root->left), 0);
        int right_gain = std::max(dfs(root->right), 0);

        // The max path sum "peaking" at this current node
        int current_path_sum = root->val + left_gain + right_gain;

        // Update the overall maximum found across the entire tree
        global_max = std::max(global_max, current_path_sum);

        // Return the max gain this node can contribute to its parent
        return root->val + std::max(left_gain, right_gain);
    }

public:
    int maxPathSum(TreeNode *root) { return solution1(root); }
};