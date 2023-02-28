import java.util.HashMap;
import java.util.Map;

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
        return solution1(s1, s2);
    }
}