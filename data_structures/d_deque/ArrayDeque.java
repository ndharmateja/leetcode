package data_structures.d_deque;

import java.util.Iterator;
import java.util.NoSuchElementException;

@SuppressWarnings("unchecked")
public class ArrayDeque<T> implements Deque<T> {
    private T[] array;

    // We only store head and size
    // because we can calculate tail easily from head and size
    private int head = 0;
    private int size = 0;

    // construct an empty randomized queue
    public ArrayDeque() {
        array = (T[]) new Object[1];
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return size;
    }

    // Resize the array to the given capacity
    // While copying it starts from the head element and
    // copies it to the copy array one by one
    // So after copying head becomes zero
    private void resize(int capacity) {
        // Iterate over all the elements one by one
        // and put it in the copy array
        T[] copy = (T[]) new Object[capacity];
        for (int i = 0; i < size; i++) {
            int index = (i + head) % array.length;
            copy[i] = array[index];
        }
        array = copy;
        head = 0;
    }

    public void addFirst(T item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Resize the array to double size if full
        if (size == array.length)
            resize(2 * array.length);

        head--;
        head = (head + array.length) % array.length;
        array[head] = item;
        size++;
    }

    public void addLast(T item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException("item to add can't be null");
        }

        // Resize the array to double size if full
        if (size == array.length)
            resize(2 * array.length);

        // Compute tail (index of the last element + 1)
        // and insert it at the tail position and increment size
        int tail = (head + size) % array.length;
        array[tail] = item;
        size++;
    }

    public T removeFirst() {
        // Throw exception if queue is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Queue is empty");
        }

        // Return head
        // Increment head after removing element
        T item = array[head];
        array[head++] = null;
        head %= array.length;
        size--;

        // Resize array to half capacity if num elements reaches quarter capacity
        if (size > 0 && size == array.length / 4)
            resize(array.length / 2);

        // Return the appropriate item
        return item;
    }

    public T removeLast() {
        // Throw exception if queue is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Queue is empty");
        }

        // Return head
        // Increment head after removing element
        int tail = (head + size) % array.length;
        T item = array[tail - 1];
        array[tail - 1] = null;
        size--;

        // Resize array to half capacity if num elements reaches quarter capacity
        if (size > 0 && size == array.length / 4)
            resize(array.length / 2);

        // Return the appropriate item
        return item;
    }

    public T peek() {
        // Throw exception if queue is empty
        if (isEmpty()) {
            throw new NoSuchElementException("Queue is empty");
        }

        return array[head];
    }

    // return an independent iterator over items in random order
    public Iterator<T> iterator() {
        return new ArrayIterator();
    }

    private class ArrayIterator implements Iterator<T> {
        int curr = head;
        int numElementsIterated = 0;

        @Override
        public boolean hasNext() {
            return numElementsIterated < size;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException("Reached the end of iterator");
            }

            numElementsIterated++;
            T nextElement = array[curr++];
            curr = curr % array.length;
            return nextElement;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}