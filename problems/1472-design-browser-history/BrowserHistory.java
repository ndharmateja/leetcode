class BrowserHistory {
    static class Node {
        String url;
        Node next;
        Node prev;
    }

    // Instance variables for the sentinel nodes
    // and the pointer to the curr url
    Node head;
    Node tail;
    Node curr;

    // We store all the urls as a DLL
    // from left to right increasing chronologically
    public BrowserHistory(String homepage) {
        this.head = new Node();
        this.tail = new Node();

        this.curr = new Node();
        this.curr.url = homepage;

        head.next = this.curr;
        this.curr.prev = head;

        tail.prev = this.curr;
        this.curr.next = tail;
    }

    // Insert one node after curr node
    // and remove all the urls after that
    // so we directly link the newNode to tail
    public void visit(String url) {
        Node newNode = new Node();
        newNode.url = url;

        this.curr.next = newNode;
        newNode.prev = this.curr;
        this.tail.prev = newNode;
        newNode.next = this.tail;

        this.curr = newNode;
    }

    // Go back 'steps' number of times
    // or stop if we reach head
    public String back(int steps) {
        for (int i = 0; i < steps; i++) {
            if (this.curr.prev == this.head)
                break;
            this.curr = this.curr.prev;
        }
        return this.curr.url;
    }

    // Go forward 'steps' number of times
    // or stop if we reach tail
    public String forward(int steps) {
        for (int i = 0; i < steps; i++) {
            if (this.curr.next == this.tail)
                break;
            this.curr = this.curr.next;
        }
        return this.curr.url;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("[");

        Node curr = this.head.next;
        while (curr != this.tail) {
            builder.append(curr.url);
            builder.append(", ");
            curr = curr.next;
        }

        builder.setLength(builder.length() - 2);
        builder.append("]");

        return builder.toString();
    }
}