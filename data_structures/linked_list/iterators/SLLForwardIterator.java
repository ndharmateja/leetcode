package data_structures.linked_list.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.linked_list.nodes.SLLNode;

public class SLLForwardIterator<T> implements Iterator<T> {
    private SLLNode<T> curr;

    /**
     * Forward iterator for a singly linked list
     * without sentinel nodes
     * (head is the first node, not the sentinel node)
     * 
     * @param head
     */
    public SLLForwardIterator(SLLNode<T> head) {
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
