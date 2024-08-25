import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution242 {

    // O(n log n) time as we sort both the strings first
    private boolean solution1(String s, String t) {
        if (s.length() != t.length())
            return false;

        if (s.equals(t))
            return true;

        char[] sChars = s.toCharArray();
        char[] tChars = t.toCharArray();

        Arrays.sort(sChars);
        Arrays.sort(tChars);

        for (int i = 0; i < sChars.length; i++) {
            if (sChars[i] != tChars[i])
                return false;
        }

        return true;
    }

    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();

        for (char c : string.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0) + 1);
        }

        return counts;
    }

    // O(n) time and O(n) space
    private boolean solution2(String s, String t) {
        return getCharCounts(s).equals(getCharCounts(t));
    }

    public boolean isAnagram(String s, String t) {
        return solution2(s, t);
    }
}