package data_structures.deque;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.iterators.linked_list.DLLForwardIterator;
import data_structures.nodes.linked_list.DLLNode;

public class LinkedDeque<T> implements Deque<T> {
    // sentinel nodes head and tail
    private DLLNode<T> head;
    private DLLNode<T> tail;
    private int size = 0;

    // construct an empty deque
    public LinkedDeque() {
        // initialize sentinel SLLNode<T>s and connect head and tail
        head = new DLLNode<T>();
        tail = new DLLNode<T>();
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
    public void addFirst(T t) {
        // Throw exception if item is null
        if (t == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Create new node with item
        DLLNode<T> newNode = new DLLNode<>();
        newNode.data = t;

        // Insert it after the head sentinel node
        head.next.prev = newNode;
        newNode.next = head.next;
        head.next = newNode;
        newNode.prev = head;

        // Increment size
        size++;
    }

    // add the item to the back
    public void addLast(T item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Create new node with item
        DLLNode<T> newNode = new DLLNode<>();
        newNode.data = item;

        // Insert it after the head sentinel node
        tail.prev.next = newNode;
        newNode.prev = tail.prev;
        tail.prev = newNode;
        newNode.next = tail;

        // Increment size
        size++;
    }

    // remove and return the item from the front
    public T removeFirst() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty");
        }

        // Adjust connections to remove the node after head
        DLLNode<T> toRemove = head.next;
        head.next = toRemove.next;
        head.next.prev = head;

        // Decrement size and return item
        size--;
        return toRemove.data;
    }

    // remove and return the item from the back
    public T removeLast() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty");
        }

        // Adjust connections to remove the node before tail
        DLLNode<T> toRemove = tail.prev;
        tail.prev = toRemove.prev;
        tail.prev.next = tail;

        // Decrement size and return item
        size--;
        return toRemove.data;
    }

    // return an iterator over items in order from front to back
    public Iterator<T> iterator() {
        return new DLLForwardIterator<>(head, tail);
    }
}