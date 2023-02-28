import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution438 {
    // Return char counts
    // Assumes string only has lowercase a-z
    // Initializes count to 0 for chars not present in string
    private Map<Character, Integer> getCharCounts(String string) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c = 'a'; c <= 'z'; c++) {
            counts.put(c, 0);
        }
        for (char c : string.toCharArray()) {
            counts.put(c, counts.get(c) + 1);
        }
        return counts;
    }

    /**
     * O(n) time and O(26) space solution
     * Reference: Solution567.java
     */
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> output = new ArrayList<>();

        if (s.length() < p.length())
            return output;

        // Initialize the window and get char counts
        int l = 0;
        int r = p.length() - 1;
        Map<Character, Integer> windowCharCounts = getCharCounts(s.substring(l, r + 1));
        Map<Character, Integer> s1CharCounts = getCharCounts(p);

        // Calculate #matches
        int matches = 0;
        for (char c = 'a'; c <= 'z'; c++)
            matches += windowCharCounts.get(c).equals(s1CharCounts.get(c)) ? 1 : 0;

        // If #matches is 26, it is a match
        if (matches == 26)
            output.add(l);

        while (r < s.length() - 1) {

            char charL = s.charAt(l++);

            // If before removal of charL
            // charL has the same count in window and p, we decrement matches
            // as we are changing it
            if (windowCharCounts.get(charL).equals(s1CharCounts.get(charL)))
                matches--;

            // Remove char at 'l' from window and increment 'l'
            windowCharCounts.put(charL, windowCharCounts.get(charL) - 1);

            // If after removal of charL
            // charL has the same count in window and p, we increment matches
            // as we are changing it
            if (windowCharCounts.get(charL).equals(s1CharCounts.get(charL)))
                matches++;

            char charR = s.charAt(++r);

            // If before addition of charR
            // charR has the same count in window and p, we decrement matches
            // as we are changing it
            if (windowCharCounts.get(charR).equals(s1CharCounts.get(charR)))
                matches--;

            // add char at 'r+1'
            windowCharCounts.put(charR, windowCharCounts.get(charR) + 1);

            // If after addition of charR
            // charR has the same count in window and p, we increment matches
            // as we are changing it
            if (windowCharCounts.get(charR).equals(s1CharCounts.get(charR)))
                matches++;

            if (matches == 26)
                output.add(l);
        }

        return output;
    }
}