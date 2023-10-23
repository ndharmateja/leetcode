package data_structures.queue;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.testing.TestUtils;

public class TestQueue {
    private static void testQueue(Queue<Integer> queue) {
        // Test size and isEmpty on empty Queue
        TestUtils.doAssertion(queue.isEmpty());
        TestUtils.doAssertion(queue.size() == 0, "Empty queue size should be 0");

        // Test if exception is thrown for peek and pop on empty Queue
        try {
            queue.dequeue();
            TestUtils.doAssertion(false, "pop on empty queue should throw an exception");
        } catch (NoSuchElementException e) {
        }
        try {
            queue.peek();
            TestUtils.doAssertion(false, "peek on empty queue should throw an exception");
        } catch (NoSuchElementException e) {
        }

        // Test push size and is Empty
        for (int i = 0; i < 100; i++) {
            queue.enqueue(i);
            TestUtils.doAssertion(queue.size() == i + 1);
            TestUtils.doAssertion(!queue.isEmpty());
        }

        // Test iterator
        Iterator<Integer> it = queue.iterator();
        for (int i = 0; i < 100; i++) {
            TestUtils.doAssertion(it.next() == i);
        }
        try {
            it.next();
            TestUtils.doAssertion(false, "next() at end of iterator should throw an exception");
        } catch (NoSuchElementException e) {
        }
        try {
            it.remove();
            TestUtils.doAssertion(false, "remove() on iterator should throw an exception");
        } catch (UnsupportedOperationException e) {
        }

        // Test peek and pop
        TestUtils.doAssertion(queue.peek() == 0);
        for (int i = 0; i < 100; i++) {
            TestUtils.doAssertion(queue.dequeue() == i);
            TestUtils.doAssertion(queue.size() == 100 - i - 1,
                    "Expected size - " + (100 - i - 1) + " Actual size - " + queue.size());
        }

        // Size should be empty at the end
        TestUtils.doAssertion(queue.isEmpty());
        TestUtils.doAssertion(queue.size() == 0);
    }

    public static void main(String[] args) {
        testQueue(new LinkedQueue<>());
        System.out.println("Testing LinkedQueue complete");
        testQueue(new ArrayQueue<>());
        System.out.println("Testing ArrayQueue complete");
    }
}
