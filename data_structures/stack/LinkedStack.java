package data_structures.stack;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class LinkedStack<T> implements Stack<T> {
    private Node head;
    private int size = 0;

    private class Node {
        T data;
        Node next;
    }

    @Override
    public void push(T t) {
        if (t == null)
            throw new IllegalArgumentException();
        Node oldHead = head;
        head = new Node();
        head.data = t;
        head.next = oldHead;
        size++;
    }

    @Override
    public T pop() {
        if (isEmpty())
            throw new NoSuchElementException();
        T t = head.data;
        head = head.next;
        return t;
    }

    @Override
    public T peek() {
        if (isEmpty())
            throw new NoSuchElementException();
        return head.data;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
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
