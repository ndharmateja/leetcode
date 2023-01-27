import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution796 {
    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    private String rotateOnce(String s) {
        return s.substring(1) + s.charAt(0);
    }

    // O(n) time and O(n^2) space solution
    public boolean solution1(String s, String goal) {
        if (s.equals(goal))
            return true;
        if (s.length() != goal.length())
            return false;
        if (!getCharCounts(s).equals(getCharCounts(goal)))
            return false;

        // Rotate string once each time and compare with goal
        for (int i = 0; i < s.length() - 1; i++) {
            s = rotateOnce(s);
            if (s.equals(goal))
                return true;
        }
        return false;
    }

    // O(n) time and O(n) space solution
    private boolean solution2(String s, String goal) {
        return s.length() == goal.length() && (s + s).contains(goal);
    }

    public boolean rotateString(String s, String goal) {
        return solution1(s, goal);
    }
}