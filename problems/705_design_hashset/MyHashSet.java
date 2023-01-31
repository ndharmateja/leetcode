class MyHashSet {
    static class Node {
        int key;
        Node next;

        Node(int key) {
            this.key = key;
        }
    }

    Node[] array;
    int size = 0;

    public MyHashSet() {
        this.array = new Node[10001];
    }

    public void add(int key) {
        // If key already exists, we don't need to add
        if (this.contains(key))
            return;

        // Insert the newly created node at the head of
        // the linked list
        int index = this.getIndex(key);
        Node node = new Node(key);

        // If the node in index is null
        // we assign the created node to the array index
        if (this.array[index] == null) {
            this.array[index] = node;
        }
        // Otherwise we make the created node as the
        // head of the linked list
        else {
            node.next = this.array[index];
            this.array[index] = node;
        }
    }

    public void remove(int key) {
        int index = this.getIndex(key);
        Node curr = this.array[index];

        // If the node in index is null
        // nothing to remove
        if (curr == null) {
            return;
        }

        // If the head itself contains the key
        // we remove the head
        // and assign the head's next node
        // to the array index
        if (curr.key == key) {
            this.array[index] = curr.next;
            return;
        }

        // Iterate till we find the key
        // and remove the node
        // If we reach the end before finding it, no removal
        Node prev = null;
        while (curr != null) {
            if (curr.key == key) {
                prev.next = curr.next;
                return;
            }
            prev = curr;
            curr = curr.next;
        }
    }

    // Hash function
    public int getIndex(int key) {
        return Integer.hashCode(key) % this.array.length;
    }

    public boolean contains(int key) {
        // Iterate through the linked list at the index
        // to see if we find the key
        int index = this.getIndex(key);
        Node curr = this.array[index];
        while (curr != null) {
            if (curr.key == key)
                return true;
            curr = curr.next;
        }
        return false;
    }
}