package data_structures.d_deque;

public class Utils {
    public static <T> void printDeque(Deque<T> deque) {
        System.out.print("Deque items: [ ");
        for (T item : deque) {
            System.out.print(item + " ");
        }
        System.out.println("]");
        System.out.println("Size: " + deque.size() + "\n");
    }
}
