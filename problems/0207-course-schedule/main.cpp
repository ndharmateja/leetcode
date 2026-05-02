#include <vector>
#include <stack>

/**
 * Finding if they can be topologically sorted is equivalent to finding
 * if the given graph is a DAG
 * So essentially this is a cycle detection problem
 * If there is a cycle then they can't be topologically sorted
 * We can check if there is a cycle using DFS and checking if there is a back edge
 * There is a back edge in DFS iff there exists a cycle
 * We can use pre and post numbers to detect back edges
 */
namespace Solution1
{
    static bool has_cycle(const std::vector<std::vector<int>> &adj_list,
                          int u, std::vector<bool> &visited,
                          std::vector<int> &pre,
                          std::vector<int> &post,
                          int &clock)
    {
        // Mark node as visited
        visited[u] = true;

        // This is the first time we are visiting this node
        // so update the pre number
        pre[u] = ++clock;

        // Run DFS each of its unvisited neighbours
        for (int v : adj_list[u])
        {
            // If u-v is a back edge, we can directly return true
            // u-v is a back edge if v is already visited but not done
            // so the pre(v) < pre(u) < post(u) < post(v)
            // To check if u and v are not done, we can check if their post numbers are -1
            // u is still not done, so post[u] will be -1
            if (visited[v] && (pre[v] < pre[u]) && (post[v] == -1))
                return true;

            // If v is already visited, skip it
            if (visited[v])
                continue;

            // If DFS on a neighbour returns true, it means that there
            // is a cycle and we don't need to continue running DFS and
            // we can immediately return true without visiting other neighbours
            if (has_cycle(adj_list, v, visited, pre, post, clock))
                return true;
        }

        // We are completely done with the vertex 'u', so we can update the post number
        post[u] = ++clock;

        // If none of the edges u->v are back edges and none of the has_cycle calls on the neighbours
        // returned true, it means that we can return false
        return false;
    }

    /**
     * DFS based solution to detect a cycle
     */
    static bool canFinish(int n, const std::vector<std::vector<int>> &edges)
    {
        // Construct the adjacency list
        // You are given an array prerequisites where prerequisites[i] = [ai, bi]
        // indicates that you must take course bi first if you want to take course ai.
        // So we add an edge from bi to ai indicating that bi has to be done before ai
        std::vector<std::vector<int>> adj_list(n);
        for (const auto &edge : edges)
        {
            // !Self loops are possible
            // So if there is an edge from a node to itself, it means that course is a prerequisite
            // to itself => cycle => we can return false
            if (edge.front() == edge.back())
                return false;
            adj_list[edge.back()].push_back(edge.front());
        }

        // Run DFS starting from each unvisited vertex and explore all the nodes
        // that it can reach and also see if there is a cycle
        int clock{0};
        std::vector<bool> visited(n, false);
        std::vector<int> pre(n, -1), post(n, -1);
        for (int i = 0; i < n; i++)
            if (!visited[i] && has_cycle(adj_list, i, visited, pre, post, clock))
                return false;

        // If we reached here it means that we don't have a cycle
        // as we'd have already returned false if there was a cycle
        return true;
    }
}

/**
 * Same solution as above except we use the enum state of unvisited/visiting/visited
 * instead of the pre and post arrays to detect back edges
 * which is much faster as lesser lookups and integer comparisons
 * and lesser space which uses one vector of uint8_t each of size n
 * instead of 2 vectors of int each of size n
 * and a visited vector of bool each of size n
 */
namespace Solution2
{
    enum class State
    {
        UNVISITED,
        VISITING,
        VISITED
    };

    static bool has_cycle(const std::vector<std::vector<int>> &adj_list,
                          int u, std::vector<State> &state)
    {
        // Mark node as visited
        state[u] = State::VISITING;

        // Run DFS each of its unvisited neighbours
        for (int v : adj_list[u])
        {
            // If u-v is a back edge, we can directly return true
            // u-v is a back edge if v is in visiting state
            if (state[v] == State::VISITING)
                return true;

            // If DFS on a neighbour returns true, it means that there
            // is a cycle and we don't need to continue running DFS and
            // we can immediately return true without visiting other neighbours
            if (state[v] == State::UNVISITED && has_cycle(adj_list, v, state))
                return true;
        }

        // We are completely done with the vertex 'u'
        state[u] = State::VISITED;

        // If none of the edges u->v are back edges and none of the has_cycle calls on the neighbours
        // returned true, it means that we can return false
        return false;
    }

    /**
     * DFS based solution to detect a cycle
     */
    static bool canFinish(int n, const std::vector<std::vector<int>> &edges)
    {
        // Construct the adjacency list
        // You are given an array prerequisites where prerequisites[i] = [ai, bi]
        // indicates that you must take course bi first if you want to take course ai.
        // So we add an edge from bi to ai indicating that bi has to be done before ai
        std::vector<std::vector<int>> adj_list(n);
        for (const auto &edge : edges)
        {
            // !Self loops are possible
            // So if there is an edge from a node to itself, it means that course is a prerequisite
            // to itself => cycle => we can return false
            if (edge.front() == edge.back())
                return false;
            adj_list[edge.back()].push_back(edge.front());
        }

        // Run DFS starting from each unvisited vertex and explore all the nodes
        // that it can reach and also see if there is a cycle
        std::vector<State> state(n, State::UNVISITED);
        for (int i = 0; i < n; i++)
            if (state[i] == State::UNVISITED && has_cycle(adj_list, i, state))
                return false;

        // If we reached here it means that we don't have a cycle
        // as we'd have already returned false if there was a cycle
        return true;
    }
}

class Solution
{
public:
    bool canFinish(int numCourses, const std::vector<std::vector<int>> &prerequisites) { return Solution2::canFinish(numCourses, prerequisites); }
};