import java.util.HashSet;
import java.util.Set;

class Solution3 {
    // O(n) time and O(n) space solution
    private int solution1(String s) {
        // Base Case
        if (s.length() == 0)
            return 0;

        int l = 0;
        int r = 0;
        int max = 1;

        Set<Character> chars = new HashSet<>();
        chars.add(s.charAt(0));

        while (r < s.length() - 1) {
            // If the char at r+1 (say char c) already exists in our sliding window
            // we move 'l' to the index after the char 'c' in our sliding window
            // ('l' could be greater than 'r' after this step as 'c' could be the char
            // at index 'r', and in this case after incrementing 'r', l and r will become
            // equal)
            // and remove all chars in the sliding window until 'c' from the set
            // So we basically keep removing the char at 'l' from the set
            // and increment 'l' as long as the char at 'r+1' is still there in the set
            // (and therefore in the sliding window)
            while (chars.contains(s.charAt(r + 1))) {
                chars.remove(s.charAt(l++));
            }

            // Add char at r+1 to the set
            chars.add(s.charAt(++r));

            // And update the max length based on new values of l and r
            max = Math.max(max, r - l + 1);
        }

        return max;
    }

    public int lengthOfLongestSubstring(String s) {
        return solution1(s);
    }
}