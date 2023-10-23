package data_structures.linked_list;

import java.util.Iterator;

import data_structures.linked_list.iterators.DLLForwardIterator;
import data_structures.nodes.linked_list.DLLNode;

public class DoublyLinkedList<T> implements Iterable<T> {
    // Sentinel nodes
    DLLNode<T> head;
    DLLNode<T> tail;
    int size;

    public DoublyLinkedList() {
        this.size = 0;
        this.head = new DLLNode<>();
        this.tail = new DLLNode<>();
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    public T get(int index) {
        if (index < 0 || index >= size) {
            return null;
        }

        DLLNode<T> curr = this.head.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        return curr.data;
    }

    public void addAtHead(T val) {
        DLLNode<T> newNode = new DLLNode<>();
        newNode.data = val;
        newNode.next = this.head.next;
        this.head.next.prev = newNode;
        this.head.next = newNode;
        newNode.prev = this.head;
        this.size++;
    }

    public void addAtTail(T val) {
        DLLNode<T> newNode = new DLLNode<>();
        newNode.data = val;
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

        DLLNode<T> curr = this.head;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        // Insert new node after curr
        DLLNode<T> newNode = new DLLNode<>();
        newNode.data = val;
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

        DLLNode<T> curr = this.head.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }

        // Delete curr
        curr.prev.next = curr.next;
        curr.next.prev = curr.prev;

        this.size--;
    }

    @Override
    public Iterator<T> iterator() {
        return new DLLForwardIterator<>(head, tail);
    }

    @Override
    public String toString() {
        if (this.size == 0) {
            return "[]";
        }

        StringBuilder builder = new StringBuilder();
        builder.append('[');
        DLLNode<T> curr = this.head;
        for (int i = 0; i < this.size; i++) {
            curr = curr.next;
            builder.append(curr.data.toString());
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
        System.out.println(dll.get(0));
        System.out.println(dll.get(1));

        for (String item : dll) {
            System.out.println(item);
        }
    }
}