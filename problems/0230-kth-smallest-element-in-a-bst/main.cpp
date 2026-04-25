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
    static void inorder_traversal(TreeNode *root, std::vector<int> &result)
    {
        if (!root)
            return;
        inorder_traversal(root->left, result);
        result.push_back(root->val);
        inorder_traversal(root->right, result);
    }

    static int solution1(TreeNode *root, int k)
    {
        // Do the inorder traversal of the tree and get the k-1 th (as k ia 1-indexed)
        // value in the inorder result
        std::vector<int> result;
        inorder_traversal(root, result);
        return result[k - 1];
    }

    /**
     * Solve using iterative inorder solution
     * See problem 94 for more details
     */
    static int solution2(TreeNode *root, int k)
    {
        // Do an iterative inorder traversal and return the kth element in the traversal
        std::stack<TreeNode *> stack;
        TreeNode *curr = root;
        int count = 0;
        while (curr || !stack.empty())
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }

            // The top most node element is the current node. Count keeps track of the #nodes
            // we have seen so far (including the current one)
            // so if count == k, then it means that this is the kth smallest element (the kth
            // element in the inorder traversal)
            // We could directly decrement k instead of count++ and check if k is 0
            // but this is more readable and intuitive.
            count++;
            curr = stack.top();
            if (count == k)
                return curr->val;

            // If it is not the kth element, then we pop the element and continue with the inorder
            // traversal. We are only popping once the check is done so that we don't need to pop
            // in when we reach the kth element.
            stack.pop();
            curr = curr->right;
        }

        // We will never reach here as the leetcode constraints say that k is in [1, n]
        throw std::out_of_range("Invalid 'k'.");
    }

public:
    int kthSmallest(TreeNode *root, int k) { return solution2(root, k); }
};