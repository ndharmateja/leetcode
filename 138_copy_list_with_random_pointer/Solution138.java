import java.util.HashMap;
import java.util.Map;

class Solution138 {
    static class Node {
        int val;
        Node next;
        Node random;

        public Node(int val) {
            this.val = val;
            this.next = null;
            this.random = null;
        }
    }

    public Node copyRandomList(Node head) {
        return solution1(head);
    }

    // O(n) time and space
    // Use a hash map to store the mappings between the old
    // and newly created nodes in the first pass while creating
    // the nodes of new list
    // Repass the second time through the old list and assign the
    // random and next to each node of new list using the nodes map
    private Node solution1(Node head) {
        Map<Node, Node> nodeMap = new HashMap<>();

        Node curr = head;
        while (curr != null) {
            nodeMap.put(curr, new Node(curr.val));
            curr = curr.next;
        }

        curr = head;
        while (curr != null) {
            Node currNew = nodeMap.get(curr);
            currNew.random = nodeMap.get(curr.random);
            currNew.next = nodeMap.get(curr.next);
            curr = curr.next;
        }

        return nodeMap.get(head);
    }
}