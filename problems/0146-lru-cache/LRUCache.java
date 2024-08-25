import java.util.HashMap;

class LRUCache {
    static class Node {
        int key;
        int value;
        Node next;
        Node prev;

        public Node(int key, int value) {
            this.key = key;
            this.value = value;
            this.next = null;
            this.prev = null;
        }
    }

    HashMap<Integer, Node> map;
    int capacity;
    Node left; // least recently used
    Node right; // most recently used

    // Method:
    // We store the most recently used on the right end
    // of the doubly linked list
    // and the least recently used on the left end of
    // the DLL
    // Every time we get/put a node, we move that node
    // to the right end of the list
    // And if capacity exceeds, we remove the left most node

    public LRUCache(int capacity) {
        this.map = new HashMap<>();
        this.capacity = capacity;

        // Sentinel nodes
        this.left = new Node(0, 0);
        this.right = new Node(0, 0);
        this.left.next = this.right;
        this.right.prev = this.left;
    }

    private void remove(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    private void insertAtRight(Node node) {
        node.next = this.right;
        node.prev = this.right.prev;
        this.right.prev.next = node;
        this.right.prev = node;
    }

    public int get(int key) {
        if (this.map.containsKey(key)) {
            Node node = this.map.get(key);

            // If this node is already the most recently used we
            // don't need to do any readjusting
            if (node != this.right) {
                this.remove(node);
                this.insertAtRight(node);
            }

            return node.value;
        }
        return -1;
    }

    public void put(int key, int value) {
        // If key already exists, we update the value
        // and bring the node to most recently used
        if (this.map.containsKey(key)) {
            Node node = this.map.get(key);

            // If this node is already the most recently used we
            // don't need to do any readjusting
            if (node != this.right) {
                this.remove(node);
                this.insertAtRight(node);
            }

            node.value = value;
            return;
        }

        // If capacity is full, we will remove the least
        // recently used node and also the value from our map
        if (this.map.size() == this.capacity) {
            Node toRemove = this.left.next;
            this.remove(toRemove);
            this.map.remove(toRemove.key);
        }

        // Create the new node and add to the right end
        // and to the map
        Node node = new Node(key, value);
        this.insertAtRight(node);
        this.map.put(key, node);
    }

    public static void main(String[] args) {
        LRUCache cache = new LRUCache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(3, 3);
    }
}