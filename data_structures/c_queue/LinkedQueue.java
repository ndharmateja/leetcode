package data_structures.c_queue;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class LinkedQueue<T> implements Queue<T> {
    private Node head;
    private Node tail;
    private int size = 0;

    private class Node {
        T data;
        Node next;
    }

    @Override
    public void enqueue(T t) {
        size++;
        Node oldTail = tail;
        tail = new Node();
        tail.data = t;
        if (isEmpty())
            head = tail;
        else
            oldTail.next = tail;
    }

    @Override
    public T dequeue() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        T t = head.data;
        head = head.next;
        if (isEmpty())
            tail = null;
        return t;
    }

    @Override
    public T peek() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        return head.data;
    }

    @Override
    public boolean isEmpty() {
        return head == null;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Iterator<T> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<T> {
        private Node curr = head;

        @Override
        public boolean hasNext() {
            return curr != null;
        }

        @Override
        public T next() {
            if (!hasNext())
                throw new NoSuchElementException();
            T t = curr.data;
            curr = curr.next;
            return t;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}
