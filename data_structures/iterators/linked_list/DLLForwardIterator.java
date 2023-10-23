package data_structures.iterators.linked_list;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.nodes.linked_list.DLLNode;

public class DLLForwardIterator<T> implements Iterator<T> {
    private DLLNode<T> curr;
    private DLLNode<T> tail;

    /**
     * Forward iterator for a doubly linked list
     * with sentinel nodes head and tail
     * 
     * @param head
     * @param tail
     */
    public DLLForwardIterator(DLLNode<T> head, DLLNode<T> tail) {
        curr = head.next;
        this.tail = tail;
    }

    @Override
    public boolean hasNext() {
        return curr != tail;
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
