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

    public void add(int index, T t) {
        if (index < 0 || index > size)
            throw new IndexOutOfBoundsException();

        if (size == array.length)
            resize(array.length * 2);

        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = t;
        size++;
    }

    private void resize(int capacity) {
        T[] copy = (T[]) new Object[capacity];
        for (int i = 0; i < size; i++) {
            copy[i] = array[i];
        }
        array = copy;
    }

    public T remove(int index) {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException();

        T toRemove = array[index];
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        array[size-- - 1] = null;

        if (size > 0 && size == array.length / 4) {
            resize(array.length / 2);
        }

        return toRemove;
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
}
