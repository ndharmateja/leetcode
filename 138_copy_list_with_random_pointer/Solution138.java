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
    // the new list
    // Repass the second time through the old list and assign the
    // random to each node of new list using the nodes map
    private Node solution1(Node head) {
        Map<Node, Node> nodeMap = new HashMap<>();

        Node currOld = head;
        Node dummy = new Node(-1);
        Node currNew = dummy;
        while (currOld != null) {
            currNew.next = new Node(currOld.val);
            nodeMap.put(currOld, currNew.next);
            currOld = currOld.next;
            currNew = currNew.next;
        }

        Node newHead = dummy.next;

        currOld = head;
        currNew = newHead;

        while (currOld != null) {
            currNew.random = nodeMap.get(currOld.random);
            currNew = currNew.next;
            currOld = currOld.next;
        }

        return newHead;
    }
}