import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution17 {
    private static Map<Character, String> map = new HashMap<>();

    // Static initialization block
    static {
        map.put('2', "abc");
        map.put('3', "def");
        map.put('4', "ghi");
        map.put('5', "jkl");
        map.put('6', "mno");
        map.put('7', "pqrs");
        map.put('8', "tuv");
        map.put('9', "wxyz");
    }

    private void backtrack(StringBuilder builder, String digits, List<String> output) {
        // if length of builder is same as digits
        // we can add this string to the output
        if (builder.length() == digits.length()) {
            output.add(builder.toString());
            return;
        }

        // Get curr digit
        char currDigit = digits.charAt(builder.length());
        // For each alphabet mapped to curr digit
        // Add alphabet to builder and continue backtrack
        // and remove after backtracking is done
        for (char alphabet : map.get(currDigit).toCharArray()) {
            builder.append(alphabet);
            backtrack(builder, digits, output);
            builder.setLength(builder.length() - 1);
        }
    }

    public List<String> letterCombinations(String digits) {
        List<String> output = new ArrayList<>();
        if (digits.length() == 0)
            return output;
        backtrack(new StringBuilder(), digits, output);
        return output;
    }
}