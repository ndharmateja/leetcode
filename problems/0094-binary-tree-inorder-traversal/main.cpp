#include <stack>
#include <vector>

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
     * Recursive function that accumulates the inorder values in the result vector
     */
    static void inorder(TreeNode *root, std::vector<int> &result)
    {
        // Base case
        if (!root)
            return;

        // General case
        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }

    /**
     * Wrapper for the recursive inorder solution
     */
    static std::vector<int> solution1(TreeNode *root)
    {
        std::vector<int> result;
        inorder(root, result);
        return result;
    }

    /**
     * Iterative inorder solution
     */
    static std::vector<int> solution2(TreeNode *root)
    {
        // Invariant is that all the elements to the left of the element about to be
        // popped from the stack have already been processed. So we can pop it and
        // process it. And then we move curr to its right and from there we keep moving left
        // adding elements to the stack until curr becomes null, thereby maintaining the invariant.

        // Create a stack for tracking the nodes and the vector for the result
        std::vector<int> result;
        std::stack<TreeNode *> stack;
        TreeNode *curr = root;

        // As long as curr is not null or there are elements in the stack
        while (curr || !stack.empty())
        {
            // If curr is not null, then it means that the left elements of curr
            // haven't been processed yet. so we add them all to the stack
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }

            // At this point curr is null, it means that all the left elements of the top most
            // element in the stack have been processed and now we process the top most
            // element in the stack
            curr = stack.top();
            stack.pop();
            result.push_back(curr->val);

            // Since all the left elements of curr have been already processed
            // we move curr to its right
            curr = curr->right;
        }

        // Return the result
        return result;
    }

public:
    std::vector<int> inorderTraversal(TreeNode *root) { return solution2(root); }
};