import java.util.ArrayList;
import java.util.List;
import java.util.Map;

class Solution17 {
    private static Map<Character, String> map = Map.of(
            '2', "abc",
            '3', "def",
            '4', "ghi",
            '5', "jkl",
            '6', "mno",
            '7', "pqrs",
            '8', "tuv",
            '9', "wxyz");

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