#include <string>
#include <vector>

class MultiSourceDFS
{
private:
    int n;
    std::vector<char> visited;
    const std::vector<std::vector<int>> &adj_list;

    void explore(int u)
    {
        visited[u] = true;
        for (int v : adj_list[u])
        {
            if (!visited[v])
                explore(v);
        }
    }

public:
    MultiSourceDFS(const std::vector<std::vector<int>> &adj_list,
                   const std::vector<int> &sources)
        : n{static_cast<int>(adj_list.size())}, visited(n),
          adj_list{adj_list}

    {
        for (int s : sources)
            if (!visited[s])
                explore(s);
    }

    bool is_reachable(int u) const { return visited[u]; }
};

class RegexParser;

class NFA
{
private:
    // M: number of characters in the re => number of states = M + 1
    // The accept state = M
    const std::string re;
    int M;
    std::vector<std::vector<int>> adj_list;

public:
    NFA(const std::string &re)
        : re{re}, M{static_cast<int>(re.size())}, adj_list(M + 1) {}

    bool recognizes(const std::string &text)
    {
        // Create a vector for storing the current states the NFA is in
        std::vector<int> curr_states, next_states;
        curr_states.reserve(M + 1);
        next_states.reserve(M + 1);

        // Get the initial states (states reachable from 0 through ε transistions)
        MultiSourceDFS dfs(adj_list, {0});
        for (int state = 0; state <= M; state++)
            if (dfs.is_reachable(state))
                curr_states.push_back(state);

        // We run the NFA simulation using each character of the
        for (char c : text)
        {
            next_states.clear();
            for (int state : curr_states)
                if (state < M)
                    if (re[state] == c || re[state] == '.')
                        next_states.push_back(state + 1);

            curr_states.clear();
            MultiSourceDFS dfs(adj_list, next_states);
            for (int state = 0; state <= M; state++)
                if (dfs.is_reachable(state))
                    curr_states.push_back(state);
        }

        // If the accept state is part of the reachable states at the end of the
        // simulation then we know that the NFA recognizes the given text
        for (int state : curr_states)
            if (state == M)
                return true;
        return false;
    }

    friend class RegexParser;
};

// C++ 17 ensures that there won't be multiple copies of the NFA object
class RegexParser
{
public:
    /**
     * Parses simple regular expressions (like Leetcode 10) with only . and *
     */
    static NFA parse_simple(const std::string &re)
    {
        NFA nfa(re);
        for (size_t i = 0; i < re.size(); i++)
        {
            if (re[i] == '*')
            {
                nfa.adj_list[i - 1].push_back(i);
                nfa.adj_list[i].push_back(i - 1);
                nfa.adj_list[i].push_back(i + 1);
            }
        }
        return nfa;
    }
};

class Solution
{
public:
    bool isMatch(const std::string &text, const std::string &re)
    {
        NFA nfa{RegexParser::parse_simple(re)};
        return nfa.recognizes(text);
    }
};