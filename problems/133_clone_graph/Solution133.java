import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Solution133 {
    class Node {
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

    // O(|V| + |E|) time and O(|V|) space
    // Straightforward DFS
    public Node cloneGraph(Node node) {
        // if node is null return null
        if (node == null)
            return null;

        // A is required map for storing the mapping
        // from node in original graph to clone graph
        // run dfs on the node
        // return clone of the node
        return dfs(node, new HashMap<>());
    }

    // This dfs is slightly different from the dfs we generally run
    // We call dfs on all the neighbors irrespective of whether
    // it has been visited or not and check if the node has been visited at the
    // start of the dfs call
    // This helps to simplify the code inside the for loop for each neighbor
    // where we don't need an if else for visited and unvisited neighbors
    // and have the same code for both
    // Returns the cloned counterpart of the node
    public Node dfs(Node node, Map<Node, Node> nodeMap) {
        // If node is already visited skip
        // We check if the node is present in the node map
        // And return the corresponding clone
        if (nodeMap.containsKey(node))
            return nodeMap.get(node);

        // Create clone of node
        // Add node -> cloneNode to map
        // mark it visited
        // We could have done this in the loop where we could have
        // create the clone for the neighbour and put in map
        // before calling dfs function on the neighbour, but
        // that would have required us to pass the neighbour clone
        // into the dfs call as well
        Node nodeClone = new Node(node.val);
        nodeMap.put(node, nodeClone);

        // For each of the neighbors
        // 1. Get the clone of the neighbor, from the map if exists or create
        // a clone of the neighbor
        // 2. Call dfs on the neighbor
        // 3. Add the neighbor clone to the neighbors of the clone node
        for (Node neighbor : node.neighbors) {
            Node neighborClone = dfs(neighbor, nodeMap);
            nodeClone.neighbors.add(neighborClone);
        }

        // Return the cloned node
        return nodeClone;
    }
}