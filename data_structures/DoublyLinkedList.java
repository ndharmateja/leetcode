package data_structures;

public class DoublyLinkedList<T> {
    static class Node<T> {
        T val;
        Node<T> prev;
        Node<T> next;

        Node(T val) {
            this.val = val;
        }
    }

    // Sentinel nodes
    Node<T> head;
    Node<T> tail;
    int size;

    public DoublyLinkedList() {
        this.size = 0;
        this.head = new Node<>(null);
        this.tail = new Node<>(null);
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    public T get(int index) {
        if (index < 0 || index >= size) {
            return null;
        }

        Node<T> curr = this.head.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        return curr.val;
    }

    public void addAtHead(T val) {
        Node<T> newNode = new Node<>(val);
        newNode.next = this.head.next;
        this.head.next.prev = newNode;
        this.head.next = newNode;
        newNode.prev = this.head;
        this.size++;
    }

    public void addAtTail(T val) {
        Node<T> newNode = new Node<>(val);
        newNode.prev = this.tail.prev;
        this.tail.prev.next = newNode;
        this.tail.prev = newNode;
        newNode.next = this.tail;
        this.size++;
    }

    public void addAtIndex(int index, T val) {
        if (index < 0 || index > size) {
            return;
        }

        Node<T> curr = this.head;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        // Insert new node after curr
        Node<T> newNode = new Node<>(val);
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

        Node<T> curr = this.head.next;
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
        Node<T> curr = this.head;
        for (int i = 0; i < this.size; i++) {
            curr = curr.next;
            builder.append(curr.val.toString());
            builder.append(" ⇌ ");
        }

        builder.setLength(builder.length() - 3);
        builder.append(']');

        return builder.toString();
    }

    public static void main(String[] args) {
        DoublyLinkedList<String> dll = new DoublyLinkedList<>();
        dll.addAtHead("dharma");
        dll.addAtHead("teja");
        System.out.println(dll);
        System.out.println(dll.get(1));
        System.out.println(dll.get(2));
    }
}