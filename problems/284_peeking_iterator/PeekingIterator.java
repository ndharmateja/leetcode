import java.util.Iterator;

class PeekingIterator implements Iterator<Integer> {
    Iterator<Integer> it;
    Integer nextValue;

    public PeekingIterator(Iterator<Integer> iterator) {
        this.it = iterator;
        this.nextValue = it.hasNext() ? it.next() : null;
    }

    // Returns the next element in the iteration without advancing the iterator.
    public Integer peek() {
        return this.nextValue;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    @Override
    public Integer next() {
        Integer toReturn = nextValue;
        nextValue = it.hasNext() ? it.next() : null;
        return toReturn;
    }

    @Override
    public boolean hasNext() {
        return this.nextValue != null;
    }
}