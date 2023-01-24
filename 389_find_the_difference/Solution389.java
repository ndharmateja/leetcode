import java.util.HashMap;
import java.util.Map;

class Solution389 {
    public char findTheDifference(String s, String t) {
        return solution1(s, t);
    }

    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    // O(n) time and O(n) space solution
    private char solution1(String s, String t) {
        Map<Character, Integer> sCounts = getCharCounts(s);
        Map<Character, Integer> tCounts = getCharCounts(t);

        for (char c : tCounts.keySet()) {
            if (!sCounts.containsKey(c) || tCounts.get(c) - sCounts.get(c) == 1) {
                return c;
            }
        }

        // We will not reach here as there is a valid solution
        return '0';
    }
}