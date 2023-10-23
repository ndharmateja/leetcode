package data_structures.c_queue;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Random;

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
        return new ArrayIterator();
    }

    private class ArrayIterator implements Iterator<T> {
        T[] iteratorArray;
        int curr = 0;

        public ArrayIterator() {
            // Create an copy array with the size of "size"
            // to store all the elements and copy all elements
            // from the randomized queue to it
            iteratorArray = (T[]) new Object[size];
            for (int i = 0; i < size; i++) {
                int index = (i + head) % array.length;
                iteratorArray[i] = array[index];
            }

            // Randomly shuffle it
            shuffle(iteratorArray);
        }

        // Fisher Yates shuffle
        // Ref:
        // https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
        private void shuffle(T[] arr) {
            int n = arr.length - 1;
            Random r = new Random();

            // Start from the last element and swap one by one. We don't
            // need to run for the first element that's why i > 0
            for (int i = n - 1; i > 0; i--) {

                // Pick a random index from 0 to i
                int j = r.nextInt(i + 1);

                // Swap arr[i] with the element at random index
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        @Override
        public boolean hasNext() {
            return curr < iteratorArray.length;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException("Reached the end of iterator");
            }

            return iteratorArray[curr++];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> rq = new RandomizedQueue<>();
        printRQ(rq);

        rq.enqueue(1);
        rq.enqueue(2);
        rq.enqueue(3);
        rq.enqueue(4);
        rq.enqueue(5);
        printRQ(rq);
        printRQ(rq);
        printRQ(rq);
        printRQ(rq);
        printRQ(rq);
        printRQ(rq);

        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());
        System.out.println(rq.peek());

        System.out.println(rq.dequeue());
        printRQ(rq);
        System.out.println(rq.dequeue());
        printRQ(rq);
        System.out.println(rq.dequeue());
        printRQ(rq);
        System.out.println(rq.dequeue());
        printRQ(rq);
    }

    private static <Item> void printRQ(RandomizedQueue<Item> rq) {
        System.out.print("Randomized items: [ ");
        for (Item item : rq) {
            System.out.print(item + " ");
        }
        System.out.println("]");
        System.out.println("Size: " + rq.size() + "\n");
    }
}