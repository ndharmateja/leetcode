import java.util.HashMap;
import java.util.Map;

class Solution1941 {
    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }
        return counts;
    }

    public boolean areOccurrencesEqual(String s) {
        Map<Character, Integer> charCounts = getCharCounts(s);
        int count = charCounts.get(s.charAt(0));
        for (char c : s.toCharArray()) {
            if (charCounts.get(c) != count)
                return false;
        }
        return true;
    }
}