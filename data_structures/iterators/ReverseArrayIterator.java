package data_structures.iterators;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ReverseArrayIterator<T> implements Iterator<T> {
    private T[] array;
    private int currIndex;
    private int size;
    private int numElementsIterated = 0;

    /**
     * Iterates in the array from index tail - 1
     * in the reverse direction
     * for numElements (circularly starts iterating from the end
     * once the start of the array is reached)
     * 
     * @param array
     * @param tail
     * @param size
     */
    public ReverseArrayIterator(T[] array, int tail, int size) {
        this.array = array;
        currIndex = tail - 1;
        this.size = size;
    }

    @Override
    public boolean hasNext() {
        return numElementsIterated < size;
    }

    @Override
    public T next() {
        if (!hasNext())
            throw new NoSuchElementException();

        T nextElement = array[currIndex--];
        currIndex = (currIndex + array.length) % array.length;
        numElementsIterated++;
        return nextElement;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
