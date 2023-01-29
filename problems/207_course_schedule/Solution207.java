import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

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

    // Topological sort
    // O(|V| + |E|) time
    // O(|E|) to build the graph by iterating over all the edges
    // O(|V|) to iterate over all the vertices to remove them one by one
    public boolean canFinish(int numCourses, int[][] prerequisites) {
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