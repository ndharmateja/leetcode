package data_structures.linked_list.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.linked_list.nodes.DLLNode;

public class DLLReverseIterator<T> implements Iterator<T> {
    private DLLNode<T> curr;
    private DLLNode<T> head;

    /**
     * Reverse iterator for a doubly linked list
     * with sentinel nodes head and tail
     * 
     * @param head
     * @param tail
     */
    public DLLReverseIterator(DLLNode<T> head, DLLNode<T> tail) {
        curr = tail.prev;
        this.head = head;
    }

    @Override
    public boolean hasNext() {
        return curr != head;
    }

    @Override
    public T next() {
        if (!hasNext())
            throw new NoSuchElementException();
        T t = curr.data;
        curr = curr.prev;
        return t;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
