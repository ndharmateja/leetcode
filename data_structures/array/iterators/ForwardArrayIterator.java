package data_structures.array.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ForwardArrayIterator<T> implements Iterator<T> {
    private T[] array;
    private int currIndex;
    private int numElements;
    private int numElementsIterated = 0;

    /**
     * Iterates in the array from index head
     * in the forward direction
     * for numElements (circularly starts iterating from the front
     * once the end is reached)
     * 
     * @param array
     * @param head
     * @param numElements
     */
    public ForwardArrayIterator(T[] array, int head, int numElements) {
        this.array = array;
        currIndex = head;
        this.numElements = numElements;
    }

    @Override
    public boolean hasNext() {
        return numElementsIterated < numElements;
    }

    @Override
    public T next() {
        if (!hasNext())
            throw new NoSuchElementException();

        T nextElement = array[currIndex++];
        currIndex = currIndex % array.length;
        numElementsIterated++;
        return nextElement;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
