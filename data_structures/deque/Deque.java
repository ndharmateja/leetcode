package data_structures.deque;

public interface Deque<T> extends Iterable<T> {
    // is the deque empty?
    public boolean isEmpty();

    // return the number of items on the deque
    public int size();

    // add the item to the front
    public void addFirst(T item);

    // add the item to the back
    public void addLast(T item);

    // remove and return the item from the front
    public T removeFirst();

    // remove and return the item from the back
    public T removeLast();
}
