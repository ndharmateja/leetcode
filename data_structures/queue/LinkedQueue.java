package data_structures.queue;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.iterators.linked_list.SLLForwardIterator;
import data_structures.nodes.linked_list.SLLNode;

public class LinkedQueue<T> implements Queue<T> {
    private SLLNode<T> head;
    private SLLNode<T> tail;
    private int size = 0;

    @Override
    public void enqueue(T t) {
        size++;
        SLLNode<T> oldTail = tail;
        tail = new SLLNode<T>();
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

        size--;
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
        return new SLLForwardIterator<>(head);
    }
}
