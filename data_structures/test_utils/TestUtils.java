package data_structures.test_utils;

public class TestUtils {
    public static void doAssertion(boolean expression, String message) {
        if (!expression) {
            throw new AssertionError(message);
        }
    }

    public static void doAssertion(boolean expression) {
        doAssertion(expression, "");
    }
}
