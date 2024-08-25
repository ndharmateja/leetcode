class MyCircularDeque {
    static class Node {
        int value;
        Node prev;
        Node next;
    }

    int capacity;
    int size;
    Node head;

    public MyCircularDeque(int k) {
        this.head = new Node();
        this.head.prev = this.head;
        this.head.next = this.head;

        this.size = 0;
        this.capacity = k;
    }

    public boolean insertFront(int value) {
        if (this.isFull())
            return false;

        Node node = new Node();
        node.value = value;

        this.head.next.prev = node;
        node.next = this.head.next;
        node.prev = this.head;
        this.head.next = node;

        this.size++;
        return true;
    }

    public boolean insertLast(int value) {
        if (this.isFull())
            return false;

        Node node = new Node();
        node.value = value;

        this.head.prev.next = node;
        node.prev = this.head.prev;
        node.next = this.head;
        this.head.prev = node;

        this.size++;
        return true;
    }

    public boolean deleteFront() {
        if (this.isEmpty())
            return false;

        Node toRemove = this.head.next;
        Node prev = toRemove.prev;
        Node next = toRemove.next;
        prev.next = next;
        next.prev = prev;

        this.size--;
        return true;
    }

    public boolean deleteLast() {
        if (this.isEmpty())
            return false;

        Node toRemove = this.head.prev;
        Node prev = toRemove.prev;
        Node next = toRemove.next;
        prev.next = next;
        next.prev = prev;

        this.size--;
        return true;
    }

    public int getFront() {
        return isEmpty() ? -1 : this.head.next.value;
    }

    public int getRear() {
        return isEmpty() ? -1 : this.head.prev.value;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public boolean isFull() {
        return this.size == this.capacity;
    }
}