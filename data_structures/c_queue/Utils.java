package data_structures.c_queue;

public class Utils {
    public static <T> void printQueue(Queue<T> queue) {
        System.out.print("Queue items: [ ");
        for (T item : queue) {
            System.out.print(item + " ");
        }
        System.out.println("]");
        System.out.println("Size: " + queue.size() + "\n");
    }
}
