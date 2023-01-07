package data_structures;

public class DoublyLinkedList {
    static class Node {
        int val;
        Node prev;
        Node next;

        Node(int val) {
            this.val = val;
        }
    }

    // Sentinel nodes
    Node head;
    Node tail;
    int size;

    public DoublyLinkedList() {
        this.size = 0;
        this.head = new Node(0);
        this.tail = new Node(0);
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    public int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }

        Node curr = this.head.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        return curr.val;
    }

    public void addAtHead(int val) {
        Node newNode = new Node(val);
        newNode.next = this.head.next;
        this.head.next.prev = newNode;
        this.head.next = newNode;
        newNode.prev = this.head;
        this.size++;
    }

    public void addAtTail(int val) {
        Node newNode = new Node(val);
        newNode.prev = this.tail.prev;
        this.tail.prev.next = newNode;
        this.tail.prev = newNode;
        newNode.next = this.tail;
        this.size++;
    }

    public void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }

        Node curr = this.head;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        // Insert new node after curr
        Node newNode = new Node(val);
        newNode.next = curr.next;
        newNode.next.prev = newNode;
        newNode.prev = curr;
        curr.next = newNode;

        this.size++;
    }

    public void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }

        Node curr = this.head.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        // Delete curr
        curr.prev.next = curr.next;
        curr.next.prev = curr.prev;

        this.size--;
    }

    @Override
    public String toString() {
        if (this.size == 0) {
            return "[]";
        }

        StringBuilder builder = new StringBuilder();
        builder.append('[');
        Node curr = this.head;
        for (int i = 0; i < this.size; i++) {
            curr = curr.next;
            builder.append(curr.val);
            builder.append(" ⇌ ");
        }

        builder.setLength(builder.length() - 4);
        builder.append(']');

        return builder.toString();
    }
}