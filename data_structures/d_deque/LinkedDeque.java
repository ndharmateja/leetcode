package data_structures.d_deque;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class LinkedDeque<Item> implements Deque<Item> {
    // sentinel nodes head and tail
    private Node head;
    private Node tail;
    private int size = 0;

    private class Node {
        Item item;
        Node next;
        Node prev;
    }

    // construct an empty deque
    public LinkedDeque() {
        // initialize sentinel nodes and connect head and tail
        head = new Node();
        tail = new Node();
        head.next = tail;
        tail.prev = head;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // return the number of items on the deque
    public int size() {
        return size;
    }

    // add the item to the front
    public void addFirst(Item item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Create new node with item
        Node newNode = new Node();
        newNode.item = item;

        // Insert it after the head sentinel node
        head.next.prev = newNode;
        newNode.next = head.next;
        head.next = newNode;
        newNode.prev = head;

        // Increment size
        size++;
    }

    // add the item to the back
    public void addLast(Item item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Create new node with item
        Node newNode = new Node();
        newNode.item = item;

        // Insert it after the head sentinel node
        tail.prev.next = newNode;
        newNode.prev = tail.prev;
        tail.prev = newNode;
        newNode.next = tail;

        // Increment size
        size++;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty");
        }

        // Adjust connections to remove the node after head
        Node toRemove = head.next;
        head.next = toRemove.next;
        head.next.prev = head;

        // Decrement size and return item
        size--;
        return toRemove.item;
    }

    // remove and return the item from the back
    public Item removeLast() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty");
        }

        // Adjust connections to remove the node before tail
        Node toRemove = tail.prev;
        tail.prev = toRemove.prev;
        tail.prev.next = tail;

        // Decrement size and return item
        size--;
        return toRemove.item;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<Item> {
        private Node current = head.next;

        @Override
        public boolean hasNext() {
            return current != tail;
        }

        @Override
        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("Reached the end of iterator");
            }

            Item item = current.item;
            current = current.next;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}