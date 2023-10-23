package data_structures.array;

import java.util.Iterator;

import data_structures.array.iterators.ForwardArrayIterator;

@SuppressWarnings("unchecked")
public class DynamicArray<T> implements Iterable<T> {
    private T[] array;
    private int size = 0;

    public DynamicArray() {
        array = (T[]) new Object[1];
    }

    public T get(int index) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();

        return array[index];
    }

    public void set(int index, T t) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();

        array[index] = t;
    }

    public void add(T t) {
        if (size == array.length)
            resize(array.length * 2);

        array[size++] = t;
    }

    private void resize(int capacity) {
        T[] copy = (T[]) new Object[capacity];
        for (int i = 0; i < size; i++) {
            copy[i] = array[i];
        }
        array = copy;
    }

    public void remove(int index) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();

        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        array[size-- - 1] = null;

        if (size > 0 && size == array.length / 4) {
            resize(array.length / 2);
        }
    }

    @Override
    public Iterator<T> iterator() {
        return new ForwardArrayIterator<>(array, 0, size);
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public String toString() {
        if (size == 0)
            return "{}";

        StringBuilder builder = new StringBuilder();
        builder.append("{");
        for (int i = 0; i < size; i++) {
            builder.append(array[i]);
            builder.append(", ");
        }
        builder.setLength(builder.length() - 2);
        builder.append("}");
        return builder.toString();
    }

    public static void main(String[] args) {
        DynamicArray<Integer> array = new DynamicArray<>();
        System.out.println(array);

        for (int i = 0; i < 10; i++) {
            array.add(i);
            System.out.println(array);
            System.out.println(array.size());
        }

        array.remove(2);
        System.out.println(array);
        System.out.println(array.size());
        array.set(2, 33);
        System.out.println(array);
        System.out.println(array.size());

        System.out.println();

        for (Integer item : array) {
            System.out.println(item);
        }

        for (int i = 0; i < 9; i++) {
            array.remove(0);
            System.out.println(array);
        }
    }
}
