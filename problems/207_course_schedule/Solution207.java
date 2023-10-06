import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

@SuppressWarnings({ "unused", "unchecked" })
class Solution207 {
    static class Vertex {
        int id;
        List<Vertex> neighbours;
        int indegree;

        public Vertex(int id, List<Vertex> neighbours, int indegree) {
            this.id = id;
            this.neighbours = neighbours;
            this.indegree = indegree;
        }

        @Override
        public String toString() {
            return "Vertex [id=" + id + ", indegree=" + indegree + "]";
        }
    }

    public boolean canFinish(int numCourses, int[][] prerequisites) {
        return solution2(numCourses, prerequisites);
    }

    // O(|V| + |E|) time
    // Standard DFS
    private boolean solution2(int numCourses, int[][] prerequisites) {
        // Build the adjacency list
        ArrayList<Integer>[] adj = buildAdjacencyList(numCourses, prerequisites);

        // Initialize sets for visited and current path
        Set<Integer> visited = new HashSet<>();
        Set<Integer> currentPath = new HashSet<>();

        // For each vertex in the graph, explore it if it is unvisited
        for (int v = 0; v < adj.length; v++) {
            if (!visited.contains(v)) {
                // If explore call returns true, we can return false
                // as it contains a cycle
                // and we don't need to explore the remaining vertices
                boolean containsCycle = explore(v, adj, visited, currentPath);
                if (containsCycle) {
                    return false;
                }
            }
            // Once a explore call is done completely
            // we don't need to reset current path as it automatically gets cleared
        }

        // If we reach here it means that there is no cycle
        // so we can return true
        return true;
    }

    private ArrayList<Integer>[] buildAdjacencyList(int numCourses, int[][] prerequisites) {
        ArrayList<Integer>[] adj = (ArrayList<Integer>[]) new ArrayList[numCourses];
        for (int i = 0; i < adj.length; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int[] prerequisite : prerequisites) {
            adj[prerequisite[1]].add(prerequisite[0]);
        }
        return adj;
    }

    // Recursively explores the vertex v through DFS
    // Returns true if there is a cycle along this exploration
    // Returns false otherwise
    private boolean explore(int v, ArrayList<Integer>[] adj, Set<Integer> visited, Set<Integer> currentPath) {
        // Add the vertex to the visited and the current path sets
        visited.add(v);
        currentPath.add(v);

        // Explore each unvisited neighbour
        for (int neighbour : adj[v]) {
            // If the neighbour is already along the current path
            // we return true
            if (currentPath.contains(neighbour)) {
                return true;
            }

            // Explore the
            if (!visited.contains(neighbour)) {
                // If exploring a neighbour contains a cycle (call returns true)
                // we can return true and we don't need to explore the remaining neighbours
                boolean containsCycle = explore(neighbour, adj, visited, currentPath);
                if (containsCycle) {
                    return true;
                }
            }
        }

        // Remove v from the current path as its exploration is done
        currentPath.remove(v);

        // Return false as no cycle has been found in neighbours
        return false;
    }

    // Topological sort
    // O(|V| + |E|) time
    // O(|E|) to build the graph by iterating over all the edges
    // O(|V|) to iterate over all the vertices to remove them one by one
    public boolean solution1(int numCourses, int[][] prerequisites) {
        // Build map of vertices
        // key: vertex id
        // value: vertex object
        Map<Integer, Vertex> vertexMap = new HashMap<>();

        // Create vertices for all courses
        for (int i = 0; i < numCourses; i++) {
            vertexMap.put(i, new Vertex(i, new ArrayList<>(), 0));
        }

        // For each prerequisite, build the graph
        // by appropriately incrementing the indegree of course
        // and also add course to the neighbours of prerequisite course
        for (int[] item : prerequisites) {
            int course = item[0];
            int prerequisite = item[1];
            vertexMap.get(course).indegree++;
            vertexMap.get(prerequisite).neighbours.add(vertexMap.get(course));
        }

        // Queue with indegree zero vertices
        // for faster retrieval of the next course
        // with zero indegree
        Queue<Vertex> indegreeZeroVertices = new LinkedList<>();
        for (Vertex v : vertexMap.values()) {
            if (v.indegree == 0) {
                indegreeZeroVertices.add(v);
            }
        }

        // Loop as long as the queue is not empty
        int counter = 0;
        while (!indegreeZeroVertices.isEmpty()) {
            // Remove a vertex with zero indegree
            Vertex currVertex = indegreeZeroVertices.poll();
            counter++;

            // Decrease the indegree for all its neighbours
            for (Vertex neighbour : currVertex.neighbours) {
                neighbour.indegree--;
                if (neighbour.indegree == 0) {
                    indegreeZeroVertices.add(neighbour);
                }
            }
        }

        // If counter is numCourses, then all courses are covered
        // else, there is a cycle and all courses cannot be done
        return counter == numCourses;
    }
}