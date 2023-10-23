package data_structures.d_deque;

public interface Deque<Item> extends Iterable<Item> {
    // is the deque empty?
    public boolean isEmpty();

    // return the number of items on the deque
    public int size();

    // add the item to the front
    public void addFirst(Item item);

    // add the item to the back
    public void addLast(Item item);

    // remove and return the item from the front
    public Item removeFirst();

    // remove and return the item from the back
    public Item removeLast();
}

