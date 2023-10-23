package data_structures.b_stack;

import java.util.Iterator;
import java.util.NoSuchElementException;

import data_structures.test_utils.TestUtils;

public class TestStack {
    private static void testStack(Stack<Integer> stack) {
        // Test size and isEmpty on empty stack
        TestUtils.doAssertion(stack.isEmpty());
        TestUtils.doAssertion(stack.size() == 0, "Empty stack size should be 0");

        // Test if exception is thrown for peek and pop on empty stack
        try {
            stack.pop();
            TestUtils.doAssertion(false, "pop on empty stack should throw an exception");
        } catch (NoSuchElementException e) {
        }
        try {
            stack.peek();
            TestUtils.doAssertion(false, "peek on empty stack should throw an exception");
        } catch (NoSuchElementException e) {
        }

        // Test push size and is Empty
        for (int i = 0; i < 100; i++) {
            stack.push(i);
            TestUtils.doAssertion(stack.size() == i + 1);
            TestUtils.doAssertion(!stack.isEmpty());
        }

        // Test iterator
        Iterator<Integer> it = stack.iterator();
        for (int i = 99; i >= 0; i--) {
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
        TestUtils.doAssertion(stack.peek() == 99);
        for (int i = 99; i >= 0; i--) {
            TestUtils.doAssertion(stack.pop() == i);
            TestUtils.doAssertion(stack.size() == i);
        }

        // Size should be empty at the end
        TestUtils.doAssertion(stack.isEmpty());
        TestUtils.doAssertion(stack.size() == 0);
    }

    public static void main(String[] args) {
        testStack(new LinkedStack<>());
        System.out.println("Testing LinkedStack complete");
        testStack(new ArrayStack<>());
        System.out.println("Testing ArrayStack complete");
    }
}
