import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Solution133 {
    static class Node {
        public int val;
        public List<Node> neighbors;

        public Node() {
            val = 0;
            neighbors = new ArrayList<Node>();
        }

        public Node(int _val) {
            val = _val;
            neighbors = new ArrayList<Node>();
        }

        public Node(int _val, ArrayList<Node> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    }

    public Node cloneGraph(Node node) {
        // if node is null return null
        if (node == null)
            return null;

        // Create a set for visited
        Set<Node> visited = new HashSet<>();

        // Create a map for storing the mapping
        // from node in original graph to clone graph
        Map<Node, Node> nodeMap = new HashMap<>();

        // Create clone of node and add to map
        Node nodeClone = new Node(node.val);
        nodeMap.put(node, nodeClone);

        // run dfs on the node
        dfs(node, visited, nodeClone, nodeMap);

        // return clone of the node
        return nodeClone;
    }

    // This dfs is slightly different from the dfs we generally run
    // We call dfs on all the neighbors irrespective of whether
    // it has been visited or not and check if the node has been visited at the
    // start of the dfs call
    // This helps to simplify the code inside the for loop for each neighbor
    // where we don't need an if else for visited and unvisited neighbors
    // and have the same code for both
    public void dfs(Node node, Set<Node> visited, Node nodeClone, Map<Node, Node> nodeMap) {
        // If node is already visited skip
        if (visited.contains(node))
            return;

        // Add node to visited
        visited.add(node);

        // For each of the neighbors
        // 1. Get the clone of the neighbor, from the map if exists or create
        // a clone of the neighbor
        // 2. Add that to the node map (if already exists, nothing will happen. just
        // a duplicate call to the put method
        // ? might slow this down a little bit due to this)
        // 3. Call dfs on the neighbor
        // 4. Add the neighbor clone to the neighbors of the clone node
        for (Node neighbor : node.neighbors) {
            Node neighborClone = nodeMap.getOrDefault(neighbor, new Node(neighbor.val));
            nodeMap.put(neighbor, neighborClone);
            dfs(neighbor, visited, neighborClone, nodeMap);
            nodeClone.neighbors.add(neighborClone);
        }
    }
}