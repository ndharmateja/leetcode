import java.util.HashSet;
import java.util.Set;

class Solution1684 {
    public int countConsistentStrings(String allowed, String[] words) {
        int output = 0;

        Set<Character> allowedSet = new HashSet<>();
        for (char c : allowed.toCharArray())
            allowedSet.add(c);

        for (String word : words) {
            boolean illegal = false;
            for (char c : word.toCharArray()) {
                if (!allowedSet.contains(c)) {
                    illegal = true;
                    break;
                }
            }
            if (!illegal)
                output++;
        }

        return output;
    }
}