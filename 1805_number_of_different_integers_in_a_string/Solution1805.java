import java.util.HashSet;
import java.util.Set;

class Solution1805 {
    // Remove all leading zeroes
    private void cleanNumber(StringBuilder number) {
        number = number.reverse();
        while (number.length() > 1 && number.charAt(number.length() - 1) == '0') {
            number.setLength(number.length() - 1);
        }
        number = number.reverse();
    }

    public int numDifferentIntegers(String word) {
        Set<String> set = new HashSet<>();
        StringBuilder number = new StringBuilder();

        for (char c : word.toCharArray()) {
            if (!Character.isDigit(c) && number.length() > 0) {
                cleanNumber(number);
                set.add(number.toString());

                number.setLength(0);
                continue;
            }
            if (Character.isDigit(c)) {
                number.append(c);
            }
        }

        if (number.length() > 0) {
            cleanNumber(number);
            set.add(number.toString());
        }

        return set.size();
    }
}