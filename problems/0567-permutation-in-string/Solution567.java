import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
class Solution567 {
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
     * Reference: https://youtu.be/UbyhOgBN834
     * The optimization we get over solution1 is that while comparing
     * the two hash maps, instead of comparing the whole hashmaps
     * we keep track of number of matches (computed initially for the
     * first window) and readjust the number of matches as we move the
     * window (2 steps to readjust the number of matches based on the
     * char removed and the char added)
     * This solution is an optimization of solution1, refer that for any doubts
     */
    private boolean solution2(String s1, String s2) {
        if (s2.length() < s1.length())
            return false;

        // Initialize the window and get char counts
        int l = 0;
        int r = s1.length() - 1;
        Map<Character, Integer> windowCharCounts = getCharCounts(s2.substring(l, r + 1));
        Map<Character, Integer> s1CharCounts = getCharCounts(s1);

        // Calculate #matches
        int matches = 0;
        for (char c = 'a'; c <= 'z'; c++)
            matches += windowCharCounts.get(c).equals(s1CharCounts.get(c)) ? 1 : 0;

        // If #matches is 26, it is a match
        if (matches == 26)
            return true;

        while (r < s2.length() - 1) {

            char charL = s2.charAt(l++);

            // If before removal of charL
            // charL has the same count in window and s1, we decrement matches
            // as we are changing it
            if (windowCharCounts.get(charL).equals(s1CharCounts.get(charL)))
                matches--;

            // Remove char at 'l' from window and increment 'l'
            windowCharCounts.put(charL, windowCharCounts.get(charL) - 1);

            // If after removal of charL
            // charL has the same count in window and s1, we increment matches
            // as we are changing it
            if (windowCharCounts.get(charL).equals(s1CharCounts.get(charL)))
                matches++;

            char charR = s2.charAt(++r);

            // If before addition of charR
            // charR has the same count in window and s1, we decrement matches
            // as we are changing it
            if (windowCharCounts.get(charR).equals(s1CharCounts.get(charR)))
                matches--;

            // add char at 'r+1'
            windowCharCounts.put(charR, windowCharCounts.get(charR) + 1);

            // If after addition of charR
            // charR has the same count in window and s1, we increment matches
            // as we are changing it
            if (windowCharCounts.get(charR).equals(s1CharCounts.get(charR)))
                matches++;

            if (matches == 26)
                return true;
        }

        return false;
    }

    /**
     * O(26*n) time and O(26) space solution
     * m - length of s1
     * n - length of s2
     * 
     * Time: O(26n) because all the chars in the given strings
     * are only lower case a-z, so the size of hash map never
     * crosses 26. So the comparison of two hashmaps takes O(26) time
     * And that is why space is also O(26)
     * 
     * To check if a particular string is a permutation of another
     * we compare their character counts
     * We keep moving the window and compare its char counts with
     * that of s1
     * 
     * @param s1
     * @param s2
     * @return
     */
    private boolean solution1(String s1, String s2) {
        if (s2.length() < s1.length())
            return false;

        // Initialize the window and get char counts
        int l = 0;
        int r = s1.length() - 1;
        Map<Character, Integer> windowCharCounts = getCharCounts(s2.substring(l, r + 1));
        Map<Character, Integer> s1CharCounts = getCharCounts(s1);

        // Check if window is a permutation of s1
        if (s1CharCounts.equals(windowCharCounts))
            return true;

        // To get the char counts of the window as we move along
        // instead of computing from scratch for each window
        // we remove char at 'l' and add char at 'r+1' to get the
        // counts of the new window
        while (r < s2.length() - 1) {
            // Remove char at 'l' from window and increment 'l'
            // We don't have to check for case where charL count is 1
            // as we are initializing the count map with 0 counts for
            // all the chars not present in the string
            char charL = s2.charAt(l++);
            windowCharCounts.put(charL, windowCharCounts.get(charL) - 1);

            // add char at 'r+1'
            char charR = s2.charAt(++r);
            windowCharCounts.put(charR, windowCharCounts.get(charR) + 1);

            // Check if window is a permutation of s1
            // and return true if permutation is found
            if (s1CharCounts.equals(windowCharCounts))
                return true;
        }

        // No permutation found
        return false;
    }

    public boolean checkInclusion(String s1, String s2) {
        return solution2(s1, s2);
    }
}