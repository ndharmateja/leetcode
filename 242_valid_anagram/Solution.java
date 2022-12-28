import java.util.HashMap;
import java.util.HashSet;

class Solution {

    private HashMap<Character, Long> getCharCounts(String s) {
        HashMap<Character, Long> counts = new HashMap<>();
        for (char c : s.toCharArray()) {
            counts.put(c, counts.getOrDefault(c, 0L) + 1);
        }
        return counts;
    }

    public boolean isAnagram(String s, String t) {
        if (s.equals(t))
            return true;
        HashMap<Character, Long> sCounts = getCharCounts(s);
        HashMap<Character, Long> tCounts = getCharCounts(t);

        HashSet<Character> chars = new HashSet<>();
        for (char c : s.toCharArray()) {
            chars.add(c);
        }
        for (char c : t.toCharArray()) {
            chars.add(c);
        }

        for (char c : chars) {
            if (sCounts.get(c) != tCounts.get(c))
                return false;
        }

        return true;
    }
}