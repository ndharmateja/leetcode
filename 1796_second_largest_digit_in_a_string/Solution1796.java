import java.util.HashSet;
import java.util.Set;

class Solution1796 {
    public int secondHighest(String s) {
        // Get all the digits in the string
        // in a set
        Set<Integer> digits = new HashSet<>();
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c))
                digits.add(c - '0');
        }

        if (digits.size() < 2)
            return -1;

        boolean largestFound = false;
        for (int i = 9; i >= 0; i--) {
            if (digits.contains(i)) {
                if (largestFound) {
                    return i;
                } else {
                    largestFound = true;
                }
            }
        }

        // we won't reach here
        return -1;
    }
}