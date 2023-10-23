package data_structures.testing;

public class TestUtils {
    public static void doAssertion(boolean expression, String message) {
        if (!expression) {
            throw new AssertionError(message);
        }
    }

    public static void doAssertion(boolean expression) {
        doAssertion(expression, "");
    }

    public static <T> boolean arrayEquals(T[] t1, T[] t2) {
        // If array lengths are different, false
        if (t1.length != t2.length) {
            return false;
        }

        // If both arrays are same object, true
        if (t1 == t2)
            return true;

        // If any of the elements aren't equal, false
        for (int i = 0; i < t1.length; i++) {
            if (!t1[i].equals(t2[i]))
                return false;
        }

        // True if we reach here
        return true;
    }
}
