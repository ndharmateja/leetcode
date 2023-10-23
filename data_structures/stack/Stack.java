package data_structures.stack;

public interface Stack<T> extends Iterable<T> {
    public void push(T t);

    public T pop();

    public T peek();

    public boolean isEmpty();

    public int size();
}
