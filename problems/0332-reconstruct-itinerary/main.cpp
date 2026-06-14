#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

class Solution
{
private:
    /**
     * Ref: https://www.youtube.com/watch?v=8MpoO2zA2l4
     * Watch the above video to get a better idea
     *
     * Theta(V + E) time and Theta(V + E) space
     */
    static std::vector<std::string> sol1(const std::vector<std::vector<std::string>> &tickets)
    {
        // Construct the adjacency list
        std::unordered_map<std::string, std::vector<std::string>> adj_list;
        for (const auto &ticket : tickets)
            adj_list[ticket.front()].push_back(ticket.back());

        // Sort each adjacency list of each node in descending order
        // To preserve the lexicographical order that is required in the question,
        // we have to traverse the neighbours in alphabetical order
        // But we also have to remove the edges as we traverse them, so if we have
        // them in the descending order, we can pop each one of the vector from the end
        // and traverse that edge
        for (auto &[src, neighbours] : adj_list)
            std::sort(neighbours.begin(), neighbours.end(), std::greater<std::string>());

        // Iterative Hierholzer's algorithm
        // The number of elements in the stack is going to be atmost #edges + 1 (which
        // is the #vertices on the Euler trail)
        // The number of elements in the result is going to be exactly #edges + 1
        std::vector<std::string> result;
        std::vector<std::string> stack;
        result.reserve(tickets.size() + 1);
        stack.reserve(tickets.size() + 1);
        stack.push_back("JFK");

        // Main loop
        while (!stack.empty())
        {
            // Use a string reference instead of a copy
            std::string &curr = stack.back();

            // If the node doesn't have an adjacency list (could happen if curr
            // is the last node in the euler trail and it doesn't have any other edges
            // than the one incoming edge) or if there are no more neighbours
            // we can add this node to the result and continue
            auto it = adj_list.find(curr);
            if (it == adj_list.end() || it->second.empty())
            {
                // ! Optimization: use std::move
                result.push_back(std::move(stack.back()));
                stack.pop_back();
                continue;
            }

            // Otherwise we pop off the last neighbour and continue execution along that path
            // ! Optimization: use std::move
            stack.push_back(std::move(it->second.back()));
            it->second.pop_back();
        }

        // We have to reverse the vector as we kept adding the nodes in the
        // opposite order of the Euler trail
        std::reverse(result.begin(), result.end());
        return result;
    }

public:
    std::vector<std::string>
    findItinerary(const std::vector<std::vector<std::string>> &tickets) { return sol1(tickets); }
};