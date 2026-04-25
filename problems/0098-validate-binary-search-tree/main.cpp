#include <limits>
#include <stack>

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
    static bool solution1(TreeNode *root, long long min, long long max)
    {
        // If no node, it is trivially true
        if (!root)
            return true;

        // We are using long long datatype to avoid overflow errors
        // Otherwise we check if root's value is in the range [min, max]
        // and the left subtree values are in the range [int_min, root->val-1]
        // and the right subtree values are in the range [root->val+1, int_max]
        return (min <= root->val && root->val <= max) &&
               solution1(root->left, min, static_cast<long long>(root->val) - 1) &&
               solution1(root->right, static_cast<long long>(root->val) + 1, max);
    }

    static bool solution1(TreeNode *root)
    {
        long long min_int = std::numeric_limits<long long>::min();
        long long max_int = std::numeric_limits<long long>::max();
        return solution1(root, min_int, max_int);
    }

    static bool solution2(TreeNode *root, int min, int max)
    {
        // If no node, it is trivially true
        if (!root)
            return true;

        // First check if the root's value is in [min, max]
        if (root->val < min || root->val > max)
            return false;

        // At this point, root's value is in [min, max]
        // If the root's value is already min and has a left child we can
        // directly return false as we know that all the values in the tree
        // are unique
        // Similarly for the right side
        if (root->val == min && root->left)
            return false;
        if (root->val == max && root->right)
            return false;

        // Check if the left subtree and the right subtree are in the valid range
        // only if they exist
        // We won't get an overflow issue as we already considered the case
        // where the left child exists and the value of the root itself is min
        // and also we are checking if the root's left exists
        if (root->left && !solution2(root->left, min, root->val - 1))
            return false;
        if (root->right && !solution2(root->right, root->val + 1, max))
            return false;

        // Return the accumulated result
        return true;
    }

    static bool solution2(TreeNode *root)
    {
        int min_int = std::numeric_limits<int>::min();
        int max_int = std::numeric_limits<int>::max();
        return solution2(root, min_int, max_int);
    }

    /**
     * Do an inorder traversal and see if all the values are in sorted order
     * See problem 94 for more details
     */
    static bool solution3(TreeNode *root)
    {
        // Edge case (not necessary in leetcode as there is atleast one node)
        // if (!root)
        //     return true;

        // When we do the iterative inorder traversal, we start curr as the root
        // and proceed by adding to the stack and updating the curr accordingly
        // For this particular problem that causes an issue as the values in the nodes
        // are in the range of [-2^31, 2^31-1], so we have trouble initializing the prev_value
        // with -2^31 as we wouldn't know if it is the initial value or an actual value
        // Another idea is to have an if statement with a flag/std::optional to see if it is the initial value
        // but that would require an if check every iteration.
        // Another solution is make the prev_value as long with a value < -2^31 and cast each value
        // into a long before checking if it is greater than the prev value.
        // So the idea is to proceed with the inorder until we find the min and init the prev value
        // and then continue the inorder traversal in the main loop
        std::stack<TreeNode *> stack;
        TreeNode *curr = root;
        while (curr->left)
        {
            stack.push(curr);
            curr = curr->left;
        }

        // At this point curr contains the min value in the tree, so we can init
        // prev_value with this
        int prev_value = curr->val;

        // After this curr should move to its right and continue the main loop
        curr = curr->right;

        // Main loop
        while (curr || !stack.empty())
        {
            // As long as curr is not null, keep moving to the left and all the nodes
            // to the stack
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }

            // At this point, curr is null and we need to process the top most node on the stack
            curr = stack.top();
            stack.pop();

            // This value should be strictly greater than the previous value
            // otherwise it is not a valid BST with unique values
            if (curr->val <= prev_value)
                return false;

            // Update the prev_val and curr node
            prev_value = curr->val;
            curr = curr->right;
        }

        // If we reach this point, then we don't have any out of order elements in the inorder traversal
        // so it is a valid BST
        return true;
    }

public:
    bool isValidBST(TreeNode *root) { return solution3(root); }
};
