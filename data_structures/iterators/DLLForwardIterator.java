package data_structures.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.nodes.linked_list.DLLNode;

public class DLLForwardIterator<T> implements Iterator<T> {
    private DLLNode<T> curr;

    public DLLForwardIterator(DLLNode<T> head) {
        curr = head;
    }

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
