package data_structures.queue;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.array.iterators.ForwardArrayIterator;

@SuppressWarnings("unchecked")
public class ArrayQueue<T> implements Queue<T> {
    private T[] array;

    // We only store head and size
    // because we can calculate tail easily from head and size
    private int head = 0;
    private int size = 0;

    // construct an empty randomized queue
    public ArrayQueue() {
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

    // add the item
    public void enqueue(T item) {
        // Throw exception if item is null
        if (item == null) {
            throw new IllegalArgumentException();
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

    // remove and return a random item
    public T dequeue() {
        // Throw exception if queue is empty
        if (isEmpty()) {
            throw new NoSuchElementException();
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

    public T peek() {
        // Throw exception if queue is empty
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        return array[head];
    }

    public Iterator<T> iterator() {
        return new ForwardArrayIterator<>(array, head, size);
    }
}