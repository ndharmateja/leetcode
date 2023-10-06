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

    public void dfs(Node node, Set<Node> visited, Node nodeClone, Map<Node, Node> nodeMap) {
        // Add node to visited
        visited.add(node);

        for (Node neighbor : node.neighbors) {
            // If we are visiting the neighbor for the first time
            // create a clone for that neighbour
            // and put it in the map
            // and run dfs on the neighbor node
            // and add the neighbor clone to the list of neighbors of the clone node
            if (!visited.contains(neighbor)) {
                Node neighborClone = new Node(neighbor.val);
                nodeMap.put(neighbor, neighborClone);
                dfs(neighbor, visited, neighborClone, nodeMap);
                nodeClone.neighbors.add(neighborClone);
            }

            // If neighbor is already visited
            // just add the connection from the clone node
            // to the clone neighbor (by getting it from the map)
            else {
                nodeClone.neighbors.add(nodeMap.get(neighbor));
            }
        }

    }
}