class TextEditor {
    static class Node {
        char c;
        Node next;
        Node prev;
    }

    // Instance variables for the sentinel nodes
    // and the pointer to the cursor
    Node head;
    Node tail;
    Node cursor;

    // We store all the chars as a DLL
    public TextEditor() {
        this.head = new Node();
        this.tail = new Node();

        this.cursor = new Node();
        this.cursor.c = '|';

        this.head.next = this.cursor;
        this.cursor.prev = this.head;
        this.cursor.next = this.tail;
        this.tail.prev = this.cursor;
    }

    // Inserts one char to the left of cursor
    private void insertChar(char c) {
        Node node = new Node();
        node.c = c;

        this.cursor.prev.next = node;
        node.prev = this.cursor.prev;
        node.next = this.cursor;
        this.cursor.prev = node;
    }

    // For each char in 'text', inserts one char to the left of cursor
    public void addText(String text) {
        for (char c : text.toCharArray()) {
            this.insertChar(c);
        }
    }

    // Delete the 'k' chars on left of cursor
    // Basically move the curr var 'k' times to the left
    // and delete everything in between
    // Moves less than 'k' times if head is reached
    public int deleteText(int k) {
        Node curr = this.cursor.prev;
        int deleteCount = 0;
        for (int i = 0; i < k; i++) {
            if (curr == this.head) {
                break;
            }
            deleteCount++;
            curr = curr.prev;
        }

        curr.next = this.cursor;
        this.cursor.prev = curr;

        return deleteCount;
    }

    // Returns the 'n' chars (max) to the left of cursor
    // as a string
    // Stops early if we reach 'head' before getting 'n' chars
    private String getNCharsLeftOfCursor(int n) {
        StringBuilder builder = new StringBuilder();
        Node curr = this.cursor;
        for (int i = 0; i < n; i++) {
            if (curr.prev == this.head)
                break;
            curr = curr.prev;
            builder.append(curr.c);
        }

        return builder.reverse().toString();
    }

    public String cursorLeft(int k) {
        // Move the cursor left 'k' times (max)
        // if the left node of cursor is not head
        if (this.cursor.prev != this.head) {
            Node cursorPrev = this.cursor.prev;
            Node cursorNext = this.cursor.next;
            Node curr = this.cursor;

            for (int i = 0; i < k; i++) {
                // stop if we reach the head
                if (curr.prev == this.head)
                    break;
                curr = curr.prev;
            }

            // Make the connections
            cursorPrev.next = cursorNext;
            cursorNext.prev = cursorPrev;
            curr.prev.next = this.cursor;
            this.cursor.prev = curr.prev;
            curr.prev = this.cursor;
            this.cursor.next = curr;

        }

        return getNCharsLeftOfCursor(10);
    }

    public String cursorRight(int k) {
        // Move the cursor right 'k' times (max)
        // if the left node of cursor is not head
        if (this.cursor.next != this.tail) {
            Node cursorPrev = this.cursor.prev;
            Node cursorNext = this.cursor.next;
            Node curr = this.cursor;

            for (int i = 0; i < k; i++) {
                // stop if we reach the tail
                if (curr.next == this.tail)
                    break;
                curr = curr.next;
            }

            // Make the connections
            cursorPrev.next = cursorNext;
            cursorNext.prev = cursorPrev;
            curr.next.prev = this.cursor;
            this.cursor.next = curr.next;
            curr.next = this.cursor;
            this.cursor.prev = curr;
        }

        return getNCharsLeftOfCursor(10);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();

        builder.append("Editor: \'");
        Node curr = this.head.next;
        while (curr != this.tail) {
            builder.append(curr.c);
            curr = curr.next;
        }
        builder.append("'");

        return builder.toString();
    }

    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        System.out.println(editor);

        editor.addText("leetcode");
        System.out.println(editor);

        System.out.println(editor.deleteText(4));
        System.out.println(editor);

        editor.addText("practice");
        System.out.println(editor);

        System.out.println(editor.cursorRight(3));
        System.out.println(editor);

        System.out.println(editor.cursorLeft(8));
        System.out.println(editor);

        System.out.println(editor.deleteText(10));
        System.out.println(editor);

        System.out.println(editor.cursorLeft(2));
        System.out.println(editor);

        System.out.println(editor.cursorRight(6));
        System.out.println(editor);
    }
}