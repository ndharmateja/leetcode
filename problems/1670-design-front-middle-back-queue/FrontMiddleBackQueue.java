class FrontMiddleBackQueue {
    static class Node {
        int value;
        Node prev;
        Node next;
    }

    Node head;
    Node tail;
    Node middle;
    int size = 0;

    public FrontMiddleBackQueue() {
        this.head = new Node();
        this.tail = new Node();
        this.middle = this.head;
        this.size = 0;

        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    public void pushFront(int val) {
        Node newNode = new Node();
        newNode.value = val;

        this.head.next.prev = newNode;
        newNode.next = this.head.next;
        this.head.next = newNode;
        newNode.prev = this.head;

        incrementSize();
    }

    public void pushMiddle(int val) {
        Node newNode = new Node();
        newNode.value = val;

        this.middle.next.prev = newNode;
        newNode.next = this.middle.next;
        newNode.prev = this.middle;
        this.middle.next = newNode;

        if (this.size % 2 == 0) {
            this.middle = this.middle.next;
        }

        incrementSize();
    }

    public void pushBack(int val) {
        Node newNode = new Node();
        newNode.value = val;

        this.tail.prev.next = newNode;
        newNode.prev = this.tail.prev;
        this.tail.prev = newNode;
        newNode.next = this.tail;

        incrementSize();
    }

    public int popFront() {
        if (this.isEmpty())
            return -1;

        Node toRemove = this.head.next;
        this.head.next = toRemove.next;
        toRemove.next.prev = this.head;

        decrementSize();
        return toRemove.value;
    }

    public int popMiddle() {
        if (this.isEmpty())
            return -1;

        Node toRemove = this.size % 2 == 0 ? this.middle : this.middle.next;
        Node prev = toRemove.prev;
        Node next = toRemove.next;
        prev.next = next;
        next.prev = prev;

        if (this.size % 2 == 0)
            this.middle = prev;

        decrementSize();
        return toRemove.value;
    }

    public int popBack() {
        if (this.isEmpty())
            return -1;

        Node toRemove = this.tail.prev;
        this.tail.prev = toRemove.prev;
        toRemove.prev.next = this.tail;

        decrementSize();
        return toRemove.value;
    }

    private boolean isEmpty() {
        return this.head.next == this.tail;
    }

    private void incrementSize() {
        this.size++;
    }

    private void decrementSize() {
        this.size--;
    }
}