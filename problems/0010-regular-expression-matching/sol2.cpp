#include <string>
#include <vector>

class RegexParser;

class NFA
{
private:
    // M: number of characters in the re => number of states = M + 1
    // The accept state = M
    const std::string re;
    int M;
    std::vector<std::vector<int>> adj_list;
    std::vector<int> curr_states;
    std::vector<int> matches;
    std::vector<int> stack;
    std::vector<char> visited;

public:
    NFA(const std::string &re)
        : re{re}, M{static_cast<int>(re.size())}, adj_list(M + 1), visited(M + 1, false)
    {
        curr_states.reserve(M + 1);
        matches.reserve(M + 1);
        stack.reserve(M + 1);
    }

    /**
     * Runs DFS on the epsilon graph starting from the given sources
     * and adds all the reachable nodes to the curr_states vector
     */
    void compute_epsilon_transitions(const std::vector<int> &sources)
    {
        // Mark all the vertices as not visited and clear the curr_states
        std::fill(visited.begin(), visited.end(), false);
        curr_states.clear();

        // Add the sources to the stack for DFS
        for (int source : sources)
        {
            stack.push_back(source);
            visited[source] = true;
            curr_states.push_back(source);
        }

        // DFS main loop
        while (!stack.empty())
        {
            int u = stack.back();
            stack.pop_back();

            for (int v : adj_list[u])
                if (!visited[v])
                {
                    stack.push_back(v);
                    visited[v] = true;
                    curr_states.push_back(v);
                }
        }
    }

    bool recognizes(const std::string &text)
    {
        // Compute the initial states (epsilon reachable from state 0)
        compute_epsilon_transitions({0});

        // We run the NFA simulation using each character of the
        for (char c : text)
        {
            // Store the matches in the matches vector
            // A state can transition (non-epsilon) if the state is '.'
            // or if the state matches the current character
            matches.clear();
            for (int state : curr_states)
                if (state < M)
                    if (re[state] == c || re[state] == '.')
                        matches.push_back(state + 1);

            // If the next states is empty at this point, then we can exit
            // at this point
            if (matches.empty())
                return false;

            // Compute the states for the next transition
            compute_epsilon_transitions(matches);
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

/**
 * Same as solution 1 except the DFS is integrated into the NFA class
 * to prevent heap allocations for DFS objects in the main loop of recognizes
 */
class Solution
{
public:
    bool isMatch(const std::string &text, const std::string &re)
    {
        NFA nfa{RegexParser::parse_simple(re)};
        return nfa.recognizes(text);
    }
};