import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution389 {
    public char findTheDifference(String s, String t) {
        return solution2(s, t);
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

    // O(n) time and O(1) space solution
    // Using difference of sum of ASCII values
    private char solution2(String s, String t) {
        int sCharsSum = 0;
        for (char c : s.toCharArray())
            sCharsSum += (int) c;

        int tCharsSum = 0;
        for (char c : t.toCharArray())
            tCharsSum += (int) c;

        return (char) (tCharsSum - sCharsSum);
    }
}