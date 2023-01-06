package data_structures;

import java.util.ArrayList;
import java.util.List;

public class MinHeap<T extends Comparable<T>> {
    List<T> array;
    int size = 0;

    public MinHeap(T[] array) {
        this.initializeArray(array);
        this.heapify();
    }

    public MinHeap() {
        this.array = new ArrayList<>();
        this.size = 0;
    }

    private void initializeArray(T[] array) {
        int numElements = 0;
        for (T t : array) {
            if (t != null) {
                numElements++;
            }
        }

        this.array = new ArrayList<>();
        this.size = numElements;

        for (T t : array) {
            if (t != null) {
                this.array.add(t);
            }
        }
    }

    // O(n) time
    private void heapify() {
        for (int i = this.parent(this.size - 1); i >= 0; i--) {
            this.siftDown(i);
        }
    }

    private int parent(int i) {
        return (i - 1) / 2;
    }

    private int leftChild(int i) {
        return 2 * i + 1;
    }

    private int rightChild(int i) {
        return 2 * i + 2;
    }

    private void siftUp(int i) {
        while (i > 0 && this.array.get(this.parent(i)).compareTo(this.array.get(i)) < 0) {
            this.swap(this.parent(i), i);
            i = this.parent(i);
        }
    }

    private void siftDown(int i) {
        int minIndex = i;

        int l = this.leftChild(i);
        if (l < size && this.array.get(l).compareTo(this.array.get(minIndex)) < 0) {
            minIndex = l;
        }

        int r = this.rightChild(i);
        if (r < size && this.array.get(r).compareTo(this.array.get(minIndex)) < 0) {
            minIndex = r;
        }

        if (i != minIndex) {
            this.swap(i, minIndex);
            this.siftDown(minIndex);
        }
    }

    private void swap(int i, int j) {
        T temp = this.array.get(i);
        this.array.set(i, this.array.get(j));
        this.array.set(j, temp);
    }

    public T extractMin() {
        T result = this.array.get(0);
        this.array.set(0, this.array.get(this.size - 1));
        this.size--;
        this.siftDown(0);
        return result;
    }

    public T getMin() {
        return this.array.get(this.size - 1);
    }

    public void insert(T t) {
        this.array.add(t);
        this.siftUp(this.size);
        this.size++;
    }

    @Override
    public String toString() {
        return this.array.subList(0, this.size).toString();
    }

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }
}
