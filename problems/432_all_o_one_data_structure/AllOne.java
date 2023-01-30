import java.util.HashMap;
import java.util.Map;

class AllOne {
    static class Node {
        String string;
        int count;
        Node prev;
        Node next;

        Node() {
            this.string = "";
        }

        Node(String string, int count) {
            this.string = string;
            this.count = count;
        }
    }

    Map<String, Node> stringNodeMap;
    Node head;
    Node tail;

    public AllOne() {
        this.stringNodeMap = new HashMap<>();
        this.head = new Node();
        this.tail = new Node();

        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    private Node insertKeyAtBeginning(String key) {
        Node node = new Node(key, 1);

        this.head.next.prev = node;
        node.next = this.head.next;
        this.head.next = node;
        node.prev = this.head;

        return node;
    }

    public void inc(String key) {
        if (stringNodeMap.containsKey(key)) {
            // Increment the count
            Node node = stringNodeMap.get(key);
            node.count++;

            // Move the node to the right until
            // the next node has a less than or equal value
            while (node.next != this.tail && node.count > node.next.count) {
                Node prev = node.prev;
                Node next = node.next;

                prev.next = next;
                next.prev = prev;

                node.next = next.next;
                next.next.prev = node;

                next.next = node;
                node.prev = next;
            }
        } else {
            // Create a new node for the 'key' with count 1
            // if it doesn't exist
            Node node = insertKeyAtBeginning(key);
            this.stringNodeMap.put(key, node);
        }
    }

    // We connect the prev and next nodes of the
    // node to each other to remove this node
    private void removeNode(Node node) {
        Node prev = node.prev;
        Node next = node.next;

        prev.next = next;
        next.prev = prev;

        node.next = null;
        node.prev = null;
    }

    public void dec(String key) {
        Node node = stringNodeMap.get(key);
        if (node.count == 1) {
            // remove the node because the count
            // will become 0 after decrementing

            // We remove the node
            // and remove the string from the map
            removeNode(node);
            this.stringNodeMap.remove(key);
        } else {
            // decrement the count
            node.count--;

            // Move the node to the left until
            // the next node has a less than or equal value
            while (node.prev != this.head && node.count < node.prev.count) {
                Node prev = node.prev;
                Node next = node.next;

                prev.next = next;
                next.prev = prev;

                node.prev = prev.prev;
                prev.prev.next = node;

                prev.prev = node;
                node.next = prev;
            }
        }
    }

    public String getMaxKey() {
        // Also handles the base case of no values in
        // our data structure as the string values in
        // head and tail are empty strings
        return this.tail.prev.string;
    }

    public String getMinKey() {
        return this.head.next.string;
    }
}