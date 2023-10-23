package data_structures.b_stack;

public interface Stack<T> extends Iterable<T> {
    public void push(T t);

    public T pop();

    public T peek();

    public boolean isEmpty();

    public int size();
}
