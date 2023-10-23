package data_structures.array;

import java.util.Iterator;

import data_structures.testing.TestUtils;

public class TestDynamicArray {
    public static void main(String[] args) {
        DynamicArray<Integer> array = new DynamicArray<>();

        TestUtils.doAssertion(array.size() == 0);
        TestUtils.doAssertion(array.isEmpty());

        for (int i = 1; i <= 100; i++) {
            array.add(i);
            TestUtils.doAssertion(array.size() == i);
            TestUtils.doAssertion(!array.isEmpty());
        }

        Iterator<Integer> it = array.iterator();
        for (int i = 1; i < 100; i++) {
            TestUtils.doAssertion(it.next() == i);
        }

        TestUtils.doAssertion(array.remove(2) == 3);
        TestUtils.doAssertion(array.size() == 99);
        TestUtils.doAssertion(!array.isEmpty());

        array.set(2, 33);
        TestUtils.doAssertion(array.get(2) == 33);
        TestUtils.doAssertion(array.size() == 99);
        TestUtils.doAssertion(!array.isEmpty());

        array.set(2, 4);
        array.add(2, 3);
        TestUtils.doAssertion(array.size() == 100);
        TestUtils.doAssertion(!array.isEmpty());
        TestUtils.doAssertion(array.get(2) == 3);
        TestUtils.doAssertion(array.get(3) == 4);

        for (int i = 0; i < 100; i++) {
            TestUtils.doAssertion(array.remove(0) == i + 1);
            TestUtils.doAssertion(array.size() == 100 - i - 1);
        }

        TestUtils.doAssertion(array.size() == 0);
        TestUtils.doAssertion(array.isEmpty());

        System.out.println("Testing DynamicArray complete");
    }
}
