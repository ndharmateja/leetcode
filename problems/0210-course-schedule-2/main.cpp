#include <vector>
#include <queue>

enum class State
{
    UNVISITED,
    VISITING,
    VISITED
};

class Solution
{
private:
    /**
     * Runs DFS and adds the elements to the result vector in the order of completion
     * of vertices and returns if there is a cycle.
     */
    static bool dfs(const std::vector<std::vector<int>> &adj,
                    int u, std::vector<State> &state,
                    std::vector<int> &result)
    {
        // Mark node as visited
        state[u] = State::VISITING;

        // Run DFS each of its unvisited neighbours
        for (int v : adj[u])
        {
            // If u-v is a back edge, we can directly return true
            // u-v is a back edge if v is in visiting state
            if (state[v] == State::VISITING)
                return true;

            // If DFS on a neighbour returns true, it means that there
            // is a cycle and we don't need to continue running DFS and
            // we can immediately return true without visiting other neighbours
            if (state[v] == State::UNVISITED && dfs(adj, v, state, result))
                return true;
        }

        // We are completely done with the vertex 'u'
        // We can add the node to the result
        state[u] = State::VISITED;
        result.push_back(u);

        // If none of the edges u->v are back edges and none of the has_cycle calls on the neighbours
        // returned true, it means that we can return false
        return false;
    }

    /**
     * DFS based solution.
     *
     * See problem 207 for more details.
     */
    static std::vector<int> solution1(int n, const std::vector<std::vector<int>> &edges)
    {
        // Run DFS and add elements in the decreasing post order for the topological sort.
        // Edge u->v => post(u) > post(v)
        // So we could keep adding elements as they finish to our resulting vector
        // But that would give us elements in reverse order as we would first add the element
        // that finished first => element with the smallest post#
        // At the end we'd have to reverse the elements
        // Instead, what we can do is if u is a prerequisite for v, instead of adding
        // the edge u->v like we normally do. We add an edge from v->u to create the
        // "reverse" dependency graph.
        // Now we can add elements in the increasing post order which will be the topological sort
        // of the original dependency graph

        // Construct the adjacency list
        // From leetcode: You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates
        // that you must take course bi first if you want to take course ai.
        // So we add an edge from bi->ai indicating that bi has to be done before ai
        // But we need the "reverse" dependency graph (read explanation above)
        // so we add edge ai->bi itself
        std::vector<std::vector<int>> adj(n);
        for (const auto &edge : edges)
        {
            // !Self loops are possible
            // So if there is an edge from a node to itself, it means that course is a prerequisite
            // to itself => cycle => we can return empty vector as no ordering is possible
            int from{edge.front()}, to{edge.back()};
            if (from == to)
                return std::vector<int>();
            adj[from].push_back(to);
        }

        // Run DFS starting from each unvisited vertex and explore all the nodes
        // that it can reach and also see if there is a cycle
        std::vector<int> result;
        std::vector<State> state(n, State::UNVISITED);
        for (int i = 0; i < n; i++)
            if (state[i] == State::UNVISITED && dfs(adj, i, state, result))
                return std::vector<int>();

        // If we reached here it means that we don't have a cycle
        // as we'd have already returned empty vector if there was a cycle
        return result;
    }

    /**
     * A DAG will always have a source. So we can keep adding the sources (and removing
     * them from the graph) to form the topological sort.
     * Kahn's algorithm. Can be parallelized.
     */
    static std::vector<int> solution2(int n, const std::vector<std::vector<int>> &edges)
    {
        // Queue for storing the sources and the vector for the result
        std::vector<int> in_degree(n, 0);
        std::queue<int> src_vertices;
        std::vector<int> result;

        // Construct the adjacency list and populate the in_degree vector
        // You are given an array prerequisites where prerequisites[i] = [ai, bi]
        // indicates that you must take course bi first if you want to take course ai.
        // So we add an edge from bi to ai indicating that bi has to be done before ai
        std::vector<std::vector<int>> adj(n);
        for (const auto &edge : edges)
        {
            // !Self loops are possible
            // So if there is an edge from a node to itself, it means that course is a prerequisite
            // to itself => cycle => we can return an empty vector
            int from{edge.back()}, to{edge.front()};
            if (from == to)
                return std::vector<int>();

            // Add the edge to the adj list and update the indegree
            adj[from].push_back(to);
            in_degree[to]++;
        }

        // Add all the indegree 0 vertices to the queue (sources)
        for (int u = 0; u < n; u++)
            if (!in_degree[u])
                src_vertices.push(u);

        // As long as the queue is not empty, we can remove a source
        // and decrement the in-degree of all the vertices it points to
        while (!src_vertices.empty())
        {
            // Pop an element and add it to the result
            int u = src_vertices.front();
            src_vertices.pop();
            result.push_back(u);

            // For each edge u->v decrement the indegree of v
            // and if v beomes a source, we add it to the queue
            for (int v : adj[u])
            {
                in_degree[v]--;
                if (!in_degree[v])
                    src_vertices.push(v);
            }
        }

        // At this point if the number of elements in the topological sort is same as n
        // then there wasn't a cycle
        // Otherwise if there are lesser elements, then there was a cycle and we stopped
        // finding more sources
        return (static_cast<int>(result.size()) == n)
                   ? result
                   : std::vector<int>();
    }

public:
    std::vector<int> findOrder(int n, std::vector<std::vector<int>> &edges) { return solution1(n, edges); }
};