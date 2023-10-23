package data_structures.d_deque;

import java.util.Iterator;

import data_structures.test_utils.TestUtils;

public class TestDeque {
    private static void testDeque(Deque<Integer> deque) {
        TestUtils.doAssertion(deque.isEmpty());
        TestUtils.doAssertion(deque.size() == 0);

        deque.addFirst(1);
        deque.addFirst(2);

        TestUtils.doAssertion(deque.size() == 2);
        TestUtils.doAssertion(!deque.isEmpty());

        TestUtils.doAssertion(deque.removeFirst() == 2);
        TestUtils.doAssertion(deque.size() == 1);
        TestUtils.doAssertion(!deque.isEmpty());

        deque.addFirst(12);
        deque.addFirst(22);

        TestUtils.doAssertion(deque.removeLast() == 1);
        TestUtils.doAssertion(deque.size() == 2);
        TestUtils.doAssertion(!deque.isEmpty());

        TestUtils.doAssertion(deque.removeFirst() == 22);
        TestUtils.doAssertion(deque.size() == 1);
        TestUtils.doAssertion(!deque.isEmpty());

        TestUtils.doAssertion(deque.removeLast() == 12);
        TestUtils.doAssertion(deque.isEmpty());

        for (int i = 0; i < 100; i++) {
            deque.addFirst(i);
            TestUtils.doAssertion(deque.size() == i + 1);
        }
        for (int i = 0; i < 100; i++) {
            deque.addLast(i);
            TestUtils.doAssertion(deque.size() == 100 + i + 1);
        }

        Iterator<Integer> it = deque.iterator();
        for (int i = 99; i >= 0; i--) {
            TestUtils.doAssertion(it.next() == i);
        }
        for (int i = 0; i < 100; i++) {
            TestUtils.doAssertion(it.next() == i);
        }

        for (int i = 99; i >= 0; i--) {
            TestUtils.doAssertion(deque.removeFirst() == i);
        }
        for (int i = 99; i >= 0; i--) {
            TestUtils.doAssertion(deque.removeLast() == i);
        }
        TestUtils.doAssertion(deque.isEmpty());
    }

    public static void main(String[] args) {
        testDeque(new LinkedDeque<Integer>());
        System.out.println("Testing LinkedDeque complete");
        testDeque(new ArrayDeque<Integer>());
        System.out.println("Testing ArrayDeque complete");
    }
}
