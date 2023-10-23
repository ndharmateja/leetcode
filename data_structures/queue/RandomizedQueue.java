package data_structures.queue;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Random;

import data_structures.array.iterators.RandomizedArrayIterator;

@SuppressWarnings("unchecked")
public class RandomizedQueue<T> implements Queue<T> {
    private T[] array;

    // We only store head and size
    // because we can calculate tail easily from head and size
    private int head = 0;
    private int size = 0;

    // construct an empty randomized queue
    public RandomizedQueue() {
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

    private void swap(int i, int j) {
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // add the item
    public void enqueue(T item) {
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

    // Gets a uniformly random index which has a value
    // [head, head + 1, .. , head + size) - we need to take care
    // of out of bound indices with modulo
    private int getRandomIndex() {
        int index = (new Random()).nextInt(size);
        return (head + index) % array.length;
    }

    // remove and return a random item
    public T dequeue() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("RandomizedQueue is empty");
        }

        // Swap head element with a randomly selected element
        // and return head
        // Increment head after removing element
        swap(head, getRandomIndex());
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

    // return a random item (but do not remove it)
    public T peek() {
        // Throw exception if deque is empty
        if (isEmpty()) {
            throw new NoSuchElementException("RandomizedQueue is empty");
        }

        // Get a random index and return the item at that index
        return array[getRandomIndex()];
    }

    // return an independent iterator over items in random order
    // Each iterator independently takes memory proportional to num items
    public Iterator<T> iterator() {
        return new RandomizedArrayIterator<>(array, head, size);
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> rq = new RandomizedQueue<>();
        Utils.printQueue(rq);

        for (int i = 0; i < 10; i++) {
            rq.enqueue(i);
        }

        System.out.print("Randomized ");
        Utils.printQueue(rq);
        System.out.print("Randomized ");
        Utils.printQueue(rq);
        System.out.print("Randomized ");
        Utils.printQueue(rq);
        System.out.print("Randomized ");
        Utils.printQueue(rq);
        System.out.print("Randomized ");
        Utils.printQueue(rq);
        System.out.print("Randomized ");
        Utils.printQueue(rq);

        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println("Random sample: " + rq.peek());
        System.out.println();

        System.out.println("Dequeued: " + rq.dequeue());
        Utils.printQueue(rq);
        System.out.println("Dequeued: " + rq.dequeue());
        Utils.printQueue(rq);
        System.out.println("Dequeued: " + rq.dequeue());
        Utils.printQueue(rq);
        System.out.println("Dequeued: " + rq.dequeue());
        Utils.printQueue(rq);
        System.out.println("Dequeued: " + rq.dequeue());
        Utils.printQueue(rq);
    }
}