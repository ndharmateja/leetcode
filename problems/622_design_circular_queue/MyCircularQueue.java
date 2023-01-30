public class MyCircularQueue {
    static class Node {
        int value;
        Node prev;
        Node next;
    }

    int capacity;
    int size;
    Node head;

    public MyCircularQueue(int k) {
        this.head = new Node();
        this.head.prev = this.head;
        this.head.next = this.head;

        this.size = 0;
        this.capacity = k;
    }

    // We enqueue elements at the rear of the list
    public boolean enQueue(int value) {
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

    // We deque from the front of the list (head.next)
    public boolean deQueue() {
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

    public int Front() {
        return isEmpty() ? -1 : this.head.next.value;
    }

    public int Rear() {
        return isEmpty() ? -1 : this.head.prev.value;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public boolean isFull() {
        return this.size == this.capacity;
    }
}