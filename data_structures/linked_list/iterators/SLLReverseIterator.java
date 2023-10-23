package data_structures.linked_list.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.nodes.linked_list.SLLNode;

public class SLLReverseIterator<T> implements Iterator<T> {
    private SLLNode<T> head;
    private int size;
    private int numElementsIterated = 0;

    /**
     * Reverse iterator for a singly linked list
     * without sentinel nodes
     * (head is the first node, not the sentinel node)
     * 
     * O(n) time for each element
     * 
     * @param head
     */
    public SLLReverseIterator(SLLNode<T> head) {
        this.head = head;
        this.size = 0;
        SLLNode<T> curr = head;
        while (curr != null) {
            this.size++;
            curr = curr.next;
        }
    }

    @Override
    public boolean hasNext() {
        return numElementsIterated < size;
    }

    @Override
    public T next() {
        if (!hasNext())
            throw new NoSuchElementException();

        SLLNode<T> curr = head;
        for (int i = 0; i < size - numElementsIterated - 1; i++) {
            curr = curr.next;
        }
        numElementsIterated++;
        return curr.data;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
