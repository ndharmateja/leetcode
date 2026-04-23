#include <vector>
#include <queue>

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
     * Checkout solution of 102 for more details
     * Do a BFS and add the last node of each level
     */
    static std::vector<int> solution1(TreeNode *root)
    {
        // Result vector
        std::vector<int> result;

        // Base case
        if (!root)
            return result;

        // Init queue
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            // At this point the queue has the nodes only from one level
            // so the node at the back of the queue is the last node in this level
            // (We could also make the right most node the node at the first by
            // adding the right node first and the left node next to the queue)
            result.push_back(q.back()->val);

            // Process all the nodes in the queue using BFS
            int num_nodes_in_curr_level = q.size();
            for (int i = 0; i < num_nodes_in_curr_level; i++)
            {
                // Get the front node from the queue and add its children if they exist
                TreeNode *curr = q.front();
                q.pop();
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }

        // Return the result
        return result;
    }

    /**
     * TODO: using DFS, go right first and left next. When we depth crosses result.size(),
     * we've encountered the right most node in that level.
     */
    static std::vector<int> solution2(TreeNode *root) { return std::vector<int>(); }

public:
    std::vector<int> rightSideView(TreeNode *root) { return solution1(root); }
};