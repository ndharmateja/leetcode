/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <vector>
#include <deque>
#include <queue>
#include <utility>

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

    static std::vector<std::vector<int>> solution1(TreeNode *root)
    {
        // Edge case where there are no nodes in the tree
        std::vector<std::vector<int>> result;
        if (!root)
            return result;

        // A standard BFS but we are also storing the level of each node
        std::queue<std::pair<int, TreeNode *>> q;
        q.push({0, root});
        while (!q.empty())
        {
            // When we pop a node from the tree, we also have its level
            // so that we can add the node's value to the appropriate level
            auto [level, curr] = q.front();
            q.pop();

            // We need to have to create a new vector for every level
            // when we encounter the first node on the level
            if (result.size() < level + 1)
                result.push_back(std::vector<int>());
            result[level].push_back(curr->val);

            // Add the children to the deque if they are not null
            if (curr->left)
                q.push({level + 1, curr->left});
            if (curr->right)
                q.push({level + 1, curr->right});
        }

        // Return the result
        return result;
    }

    static std::vector<std::vector<int>> solution2(TreeNode *root)
    {
        // Edge case
        std::vector<std::vector<int>> result;
        if (!root)
            return result;

        // We know how BFS processes nodes level by level
        // and that at any point we are going to have nodes from 2 levels
        // and sometimes we only have nodes from one level
        // which is where we can figure out what the exact nodes of that level are
        // Initially it is going to be 1 for the root
        // Since we know how many nodes to process in a level, we have an inner for loop
        // that processes each node
        // We are using a deque so that we can use the std::transform to create a vector
        // of all the nodes in the current level
        std::deque<TreeNode *> q;
        q.push_back(root);
        while (!q.empty())
        {
            // At this point we only have nodes from one level
            // and we can add all the nodes from the deque into the vector
            size_t num_nodes_in_curr_level = q.size();
            std::vector<int> current_level_values(num_nodes_in_curr_level);
            std::transform(q.begin(), q.end(),
                           current_level_values.begin(),
                           [](TreeNode *node)
                           { return node->val; });
            result.push_back(std::move(current_level_values));

            // Process each node in the current level and add its children to the deque
            for (size_t i = 0; i < num_nodes_in_curr_level; i++)
            {
                TreeNode *curr = q.front();
                q.pop_front();

                if (curr->left)
                    q.push_back(curr->left);
                if (curr->right)
                    q.push_back(curr->right);
            }
        }

        // Return the result
        return result;
    }

    static std::vector<std::vector<int>> solution3(TreeNode *root)
    {
        // Edge case
        std::vector<std::vector<int>> result;
        if (!root)
            return result;

        // Very similar to solution 2 but we add the nodes of the current level
        // inside the for loop
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            // At this point we only have nodes from one level
            // and we can add all the nodes from the deque into the vector
            size_t num_nodes_in_curr_level = q.size();
            std::vector<int> current_level_values(num_nodes_in_curr_level);

            // Process each node in the current level and add its children to the deque
            for (size_t i = 0; i < num_nodes_in_curr_level; i++)
            {
                TreeNode *curr = q.front();
                q.pop();

                // Populate the current level vector with the appropriate value
                current_level_values[i] = curr->val;

                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
            result.push_back(std::move(current_level_values));
        }

        // Return the result
        return result;
    }

public:
    std::vector<std::vector<int>> levelOrder(TreeNode *root) { return solution3(root); }
};